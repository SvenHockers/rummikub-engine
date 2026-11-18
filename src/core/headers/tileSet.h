//
// Created by Sven Hockers on 11/18/26.
//

#ifndef RUMMIKUB_ENGINE_TILESET_H
#define RUMMIKUB_ENGINE_TILESET_H
#include <vector>
#include <optional>
#include <span>

#include "tileId.h"

namespace Core {
    class TileSet final {
        public:
            [[nodiscard]] static TileSet ordered();
            [[nodiscard]] static TileSet shuffeld(std::uint64_t seed);

            [[nodiscard]] static TileSet from_remaining(std::vector<TileId> remaining);

            [[nodiscard]] std::optional<TileId> peek() const noexcept;
            [[nodiscard]] std::optional<TileId> draw() const noexcept;
            [[nodiscard]] bool empty() const noexcept { return tiles_.empty(); }
            [[nodiscard]] std::size_t size() const noexcept { return tiles_.size(); }
            [[nodiscard]] std::span<const TileId> remaining() const noexcept { return tiles_; }

        private:
            explicit TileSet(std::vector<TileId> tiles) : tiles_(std::move(tiles)) {}
            std::vector<TileId> tiles_;
    };
}

#endif //RUMMIKUB_ENGINE_TILESET_H
