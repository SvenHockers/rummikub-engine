//
// Created by Sven Hockers on 11/17/26.
//

#ifndef RUMMIKUB_ENGINE_RACK_H
#define RUMMIKUB_ENGINE_RACK_H
#include <initializer_list>
#include <vector>
#include <span>

#include "tileId.h"

namespace Core {
    class Rack final {
        public:
            Rack() = default;
            Rack(std::initializer_list<TileId> tiles);

            void add(TileId tile);  // throws std::invalid_argument on duplicates
            [[nodiscard]] bool remove(TileId tile) noexcept;
            [[nodiscard]] bool contains(TileId tile) const noexcept;
            [[nodiscard]] bool empty() const noexcept { return tiles_.empty(); }
            [[nodiscard]] std::size_t size() const noexcept { return tiles_.size(); }
            [[nodiscard]] std::span<const TileId> tiles() const noexcept { return tiles_; }
            [[nodiscard]] int penalty() const noexcept;

            void swap(Rack& other) noexcept { tiles_.swap(other.tiles_); }

        private:
            std::vector<TileId> tiles_;
    };
}

#endif //RUMMIKUB_ENGINE_RACK_H
