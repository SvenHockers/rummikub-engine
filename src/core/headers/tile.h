
#ifndef RUMMIKUB_ENGINE_TILE_H
#define RUMMIKUB_ENGINE_TILE_H

#include <cstdint>
#include <optional>

namespace Core {
    inline constexpr int COLOUR_COUNT = 4;
    inline constexpr int TILE_MIN_VALUE = 1;
    inline constexpr int TILE_MAX_VALUE = 13;
    inline constexpr int NUMBER_OF_SETS = 2;
    inline constexpr int JOKER_COUNT = 2;
    inline constexpr int NUMBERED_FACES = COLOUR_COUNT * TILE_MAX_VALUE;
    inline constexpr int TOTAL_NUMBER_OF_TILES = NUMBERED_FACES * NUMBER_OF_SETS + JOKER_COUNT;

    enum class TileColour : std::uint8_t {
        red = 0,
        blue = 1,
        green = 2,
        black = 3,
    };

    [[nodiscard]] constexpr bool valid_colour(TileColour colour) noexcept {
        return static_cast<unsigned int>(colour) < static_cast<unsigned int>(COLOUR_COUNT);
    }

    class Tile final {
        public:
            [[nodiscard]] static constexpr Tile numbered(TileColour colour, int value) {
                if (!valid_colour(colour) || value < TILE_MIN_VALUE || value > TILE_MAX_VALUE) {
                    throw std::out_of_range("numbered tile requires a valid colour and value in [1, 13]");
                }
                const auto colour_index = static_cast<int>(colour);
                return Tile(static_cast<std::uint8_t>(colour_index * TILE_MAX_VALUE + value - 1));
            }

            [[nodiscard]] static constexpr Tile joker() noexcept { return Tile(JOKER_FACE); }

            [[nodiscard]] constexpr bool is_joker() const noexcept { return encoded_ == JOKER_FACE; }

            [[nodiscard]] constexpr std::optional<TileColour> colour() const noexcept {
                if (is_joker()) return std::nullopt;
                return static_cast<TileColour>(encoded_ / TILE_MAX_VALUE);
            }

            [[nodiscard]] constexpr std::optional<std::uint8_t> value() const noexcept {
                if (is_joker()) return std::nullopt;
                return static_cast<std::uint8_t>(encoded_ % TILE_MAX_VALUE + 1);
            }

            [[nodiscard]] constexpr std::uint8_t face_index() const noexcept { return encoded_; }

            friend constexpr bool operator==(Tile, Tile) noexcept = default;

        private:
            static constexpr std::uint8_t JOKER_FACE = NUMBERED_FACES;
            explicit constexpr Tile(std::uint8_t encoded) noexcept : encoded_(encoded) {}
            std::uint8_t encoded_;
        };
}

#endif // RUMMIKUB_ENGINE_TILE_H
