
#pragma once

#include <vector>
#include <string>
#include <memory>

namespace parser
{
	enum class Piece;
	struct ITwixtParser;

	using std::uint16_t;
	using Position = std::pair<uint16_t, uint16_t>;
	using MovesPositions = std::vector<std::pair<Position, Position>>;
	using BoardRepresentation = std::vector<std::vector<Piece>>;
	using STNGameRepresentation = std::pair<BoardRepresentation, MovesPositions>;
	using PTGGameRepresentation = std::vector<std::tuple<Position, Position, bool>>;
	using TwixtParserPtr = std::shared_ptr<ITwixtParser>;

	enum class __declspec(dllexport) Piece
	{
		Empty,
		FirstPlayer,
		SecondPlayer
	};

	struct __declspec(dllexport) ITwixtParser
	{

		static TwixtParserPtr Produce();

		virtual size_t LoadPTG(std::string_view path) = 0;
		virtual bool SavePTG(std::string_view path) = 0;

		static STNGameRepresentation LoadSTN(std::string_view path);
		static bool SaveSTN(const STNGameRepresentation& game, std::string_view path);

		virtual void AddColumn(const Position& position) = 0;
		virtual void AddBridge(bool removed, const Position& firstPos, const Position& secondPos) = 0;

		virtual PTGGameRepresentation GetGamePreview(int historyIndex) const = 0;

		virtual void Clear() = 0;

		virtual ~ITwixtParser() = default;

	};
}

