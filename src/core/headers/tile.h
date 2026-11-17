
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

inline constexpr int TOTAL_NUMBER_OF_TILES =
    NUMBER_OF_SETS *
    TILE_MAX_VALUE *
    COLOUR_COUNT +
    JOKER_COUNT;

enum class TileColour : std::uint8_t {
    red   = 0,
    blue  = 1,
    green = 2,
    black = 3
};

class Tile final {
public:
    static constexpr std::optional<Tile> numbered(
        TileColour colour,
        std::uint8_t value
    ) noexcept {
        auto c = static_cast<std::uint8_t>(colour);

        if (c >= COLOUR_COUNT ||
            value < TILE_MIN_VALUE ||
            value > TILE_MAX_VALUE) {
            return std::nullopt;
        }

        return Tile{
            static_cast<std::uint8_t>(
                c * TILE_MAX_VALUE + (value - 1)
            )
        };
    }

    static constexpr Tile joker() noexcept {
        return Tile{JOKER_CODE};
    }

    constexpr bool is_joker() const noexcept {
        return encoded_ == JOKER_CODE;
    }

    constexpr std::optional<TileColour>
    colour() const noexcept {
        if (is_joker()) {
            return std::nullopt;
        }

        return static_cast<TileColour>(
            encoded_ / TILE_MAX_VALUE
        );
    }

    constexpr std::optional<std::uint8_t>
    value() const noexcept {
        if (is_joker()) {
            return std::nullopt;
        }

        return static_cast<std::uint8_t>(
            encoded_ % TILE_MAX_VALUE + 1
        );
    }

    constexpr bool operator==(const Tile&) const = default;

private:
    static constexpr std::uint8_t JOKER_CODE = 52;
    explicit constexpr Tile(std::uint8_t encoded) noexcept : encoded_(encoded) {}

    std::uint8_t encoded_;
};
}

#endif // RUMMIKUB_ENGINE_TILE_H
