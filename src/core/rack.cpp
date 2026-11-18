//
// Created by Sven Hockers on 11/17/26.
//
#include <algorithm>
#include <stdexcept>

#include "./headers/rack.h"

namespace Core {
    Rack::Rack(std::initializer_list<TileId> tiles) {
        for (const auto& tile : tiles) add(tile);
    }

    void Rack::add(const TileId id) {
        const auto tilePosition = std::lower_bound(tiles_.begin(), tiles_.end(), id);
        tiles_.insert(tilePosition, id);
    }

    bool Rack::remove(const TileId id) noexcept {
        const auto tilePosition = std::lower_bound(tiles_.begin(), tiles_.end(), id);
        if (tilePosition == tiles_.end()) return false;
        tiles_.erase(tilePosition);
        return true;
    }

    bool Rack::contains(TileId id) const noexcept {
        return std::binary_search(tiles_.begin(), tiles_.end(), id);
    }

    int Rack::penalty() const noexcept {
        int total = 0;
        for (const auto id : tiles_) {
            total += id.is_joker() ? 30 : static_cast<int>(*id.face().value());
        }
        return total;
    }
}

