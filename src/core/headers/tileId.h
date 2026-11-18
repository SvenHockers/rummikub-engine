//
// Created by Sven Hockers on 11/17/26.
//

#ifndef RUMMIKUB_ENGINE_TILEID_H
#define RUMMIKUB_ENGINE_TILEID_H
#include "tile.h"

namespace Core {
    // TileId is the implementation of Tile and represents the physical Tiles and generates all game tiles
    class TileId final {
        public:
            [[nodiscard]] static constexpr TileId from_raw(int raw) {
                if (raw < 0 || raw >= TOTAL_NUMBER_OF_TILES) {
                    throw std::out_of_range("physical TileId must be in [0, 105]");
                }
                return TileId(static_cast<std::uint8_t>(raw));
            }

            [[nodiscard]] static constexpr TileId numbered(TileColour colour, int value, int copy = 0) {
                if (copy < 0 || copy >= NUMBER_OF_SETS) {
                    throw std::out_of_range("numbered tile copy index must be 0 or 1");
                }
                const auto face = Tile::numbered(colour, value);
                return from_raw(static_cast<int>(face.face_index()) + copy * NUMBERED_FACES);
            }

            [[nodiscard]] static constexpr TileId joker(int copy = 0) {
                if (copy < 0 || copy >= JOKER_COUNT) {
                    throw std::out_of_range("joker copy index must be 0 or 1");
                }
                return from_raw(NUMBERED_FACES * NUMBER_OF_SETS + copy);
            }

            [[nodiscard]] constexpr std::uint8_t raw() const noexcept { return raw_; }
            [[nodiscard]] constexpr bool is_joker() const noexcept {
                return raw_ >= NUMBERED_FACES * NUMBER_OF_SETS;
            }
            [[nodiscard]] constexpr Tile face() const noexcept {
                if (is_joker()) return Tile::joker();
                const auto face_index = raw_ % NUMBERED_FACES;
                return Tile::numbered(static_cast<TileColour>(face_index / TILE_MAX_VALUE), static_cast<int>(face_index % TILE_MAX_VALUE) + 1);
            }
            [[nodiscard]] constexpr int copy_index() const noexcept {
                return is_joker() ? static_cast<int>(raw_) - NUMBERED_FACES * NUMBER_OF_SETS
                                  : raw_ / NUMBERED_FACES;
            }

            friend constexpr auto operator<=>(TileId, TileId) noexcept = default;

        private:
            explicit constexpr TileId(std::uint8_t raw) noexcept : raw_(raw) {}
            std::uint8_t raw_;
    };
}

#endif //RUMMIKUB_ENGINE_TILEID_H
