#ifndef OCT_OCTREE_HPP
#define OCT_OCTREE_HPP

#include <array>
#include <memory>
#include "bounds.hpp"
#include "dim.hpp"

namespace oct{
template<typename TNum> class octree;

namespace detail{
template<typename T, typename... TArgs> auto make_unique(TArgs&&... args) -> std::unique_ptr<T>
		{ return (std::unique_ptr<T>(new T(std::forward<TArgs>(args)...))); }

template<typename TNum, typename TPred> auto for_each(const octree<TNum>& tree,
			const typename octree<TNum>::node& root, TPred pred) -> void;
}

template<typename TNum> class octree{
	struct node{
		node(const bounds<TNum>& b): bound(b){}
		node(const dim<TNum>& pos, const dim<TNum>& size): bound(pos, size){}

		node(const node&) = delete;
		node(node&&) = default;

		auto operator=(const node&) -> node& = delete;
		auto operator=(node&&) -> node& = default;

		auto is_empty()const noexcept -> bool { return (point == nullptr); }
		auto is_leaf()const noexcept -> bool { return (children[0] == nullptr); }

		const bounds<TNum> bound;
		std::unique_ptr<dim<TNum>> point;
		std::array<std::unique_ptr<node>, 8> children;
	};

	template<typename TNumT, typename TPred> friend auto detail::for_each(const octree<TNumT>& tree,
			const typename octree<TNumT>::node& root, TPred pred) -> void;

	template<typename TNumT, typename TPred> friend auto for_each(const octree<TNumT>& tree, TPred pred) -> void;

public:
	octree(const bounds<TNum>& b): m_root(b){}
	octree(const octree<TNum>&) = delete;
	octree(octree<TNum>&&) = default;

	auto operator=(const octree<TNum>&) -> octree<TNum>& = delete;
	auto operator=(octree<TNum>&&) -> octree<TNum>& = default;

	auto insert(const dim<TNum>& pos) -> void { insert(pos, m_root); }

	auto remove(const dim<TNum>& pos) -> void {
		auto n = find(pos, m_root);
		if(n.second){
			n.first -> point = nullptr;
		}
	}

	auto find(const dim<TNum>& pos) -> const dim<TNum>* {
		const auto n = find(pos, m_root);
		return (n.second? (n.first -> point.get()): (nullptr));
	}

	auto clear() -> void { clear(m_root); }

private:
	auto insert(const dim<TNum>& pos, node& root) -> bool {
		if(not find(pos, root).second){
			if(root.is_empty()){
				root.point = detail::make_unique<dim<TNum>>(pos);
			}else{
				if(root.is_leaf()){
					split_node(root);
				}

				for(auto& i: root.children){
					if(contains(i -> bound, pos) and insert(pos, *i)){
						return (true);
					}
				}
			}
		}

		return (false);
	}

	auto find(const dim<TNum>& pos, node& root) -> std::pair<node*, bool> {
		if(contains(root.bound, pos)){
			if(not root.is_empty() and  *(root.point) == pos){
				return (std::make_pair(&root, true));
			}

			if(not root.is_leaf()){
				for(auto& i: root.children){
					auto n = find(pos, *i);
					if(n.second){
						return (std::move(n));
					}
				}
			}
		}

		return (std::make_pair(&root, false));
	}

	auto clear(node& n) -> void {
		if(not n.is_empty()){
			n.point = nullptr;
		}

		if(not n.is_leaf()){
			for(auto& i: n.children){
				clear(*i);
			}
		}
	}

	auto split_node(node& n) -> void {
		const auto& pos = n.bound.get_position();
		const auto half_size = n.bound.get_size() / 2.0f;

		n.children[0] = detail::make_unique<node>(pos, half_size);
		n.children[1] = detail::make_unique<node>(dim<TNum>(pos.x, pos.y, pos.z + half_size.z), half_size);

		n.children[2] = detail::make_unique<node>(dim<TNum>(pos.x, pos.y + half_size.y, pos.z), half_size);
		n.children[3] = detail::make_unique<node>(dim<TNum>(pos.x, pos.y + half_size.y, pos.z + half_size.z), half_size);

		n.children[4] = detail::make_unique<node>(dim<TNum>(pos.x + half_size.x, pos.y + half_size.y, pos.z), half_size);
		n.children[5] = detail::make_unique<node>(pos + half_size, half_size);

		n.children[6] = detail::make_unique<node>(dim<TNum>(pos.x + half_size.x, pos.y, pos.z), half_size);
		n.children[7] = detail::make_unique<node>(dim<TNum>(pos.x + half_size.x, pos.y, pos.z + half_size.z), half_size);
	}

	node m_root;
};

namespace detail{
template<typename TNum, typename TPred> auto for_each(const octree<TNum>& tree,
		const typename octree<TNum>::node& root, TPred pred) -> void {

	if(not root.is_empty()){
		pred(tree, *(root.point));
	}

	if(not root.is_leaf()){
		for(const auto& i: root.children){
			for_each<TNum, TPred>(tree, *i, pred);
		}
	}
}

}

template<typename TNum, typename TPred> auto for_each(const octree<TNum>& tree, TPred pred) -> void
		{ detail::for_each<TNum, TPred>(tree, tree.m_root, pred); }

}

#endif
