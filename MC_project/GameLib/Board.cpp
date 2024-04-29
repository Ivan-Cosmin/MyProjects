#include <regex>
#include <random>

#include "Board.h"
#include "Column.h"
#include "MinedColumn.h"

Board::Board(const uint16_t& size)
	: m_matrix{ size, std::vector<IColumnPtr>{size, nullptr}}
	, m_firstPlayerPath {size, std::vector<bool>(size, 0)}
	, m_secondPlayerPath {size, std::vector<bool>(size, 0)}
{
	// Empty
}

bool Board::ValidPosition(const int16_t& row, const int16_t& column) const
{
	if (row < 0 || row >= m_matrix.size() || column < 0 || column >= m_matrix.size())
	{
		return false;
	}
	else if (row == 0 && column == 0)
	{
		return false;
	}
	else if (row == 0 && column == m_matrix.size() - 1)
	{
		return false;
	}
	else if (row == m_matrix.size() - 1 && column == 0)
	{
		return false;
	}
	else if (row == m_matrix.size() - 1 && column == m_matrix.size() - 1)
	{
		return false;
	}
	return true;
}

bool Board::ValidPlaceColumn(const Position& position) const
{
	if (!ValidPosition(position.GetRow(), position.GetColumn()))
	{
		return false;
	}
	if (m_matrix[position.GetRow()][position.GetColumn()] != nullptr)
	{
		return false;
	}

	return true;
}

std::vector<std::string> Board::GetColumnConnections(const Position& position) const
{
	std::vector<std::string> bridgeKeyList;
	std::pair<uint16_t, uint16_t> start, end;
	static const uint8_t kMaximumSpan = 2;
	auto& [startRow, startColumn] = start;
	auto& [endRow, endColumn] = end;

	startRow = position.GetRow() - kMaximumSpan < 0 ? 0 : position.GetRow() - kMaximumSpan;
	startColumn = position.GetColumn() - kMaximumSpan < 0 ? 0 : position.GetColumn() - kMaximumSpan;
	endRow = position.GetRow() + kMaximumSpan > GetSize() - 1 ? GetSize() - 1 : position.GetRow() + kMaximumSpan;
	endColumn = position.GetColumn() + kMaximumSpan > GetSize() - 1 ? GetSize() - 1 : position.GetColumn() + kMaximumSpan;

	for (uint16_t row = startRow; row <= endRow; ++row)
	{
		for (uint16_t column = startColumn; column <= endColumn; ++column)
		{
			const auto& currentPosition = Position{ row, column };
			const auto& firstKey = MakeKey(currentPosition, position);
			const auto& secondKey = MakeKey(position, currentPosition);

			if (m_bridges.find(firstKey) != m_bridges.end()) 
			{
				bridgeKeyList.push_back(firstKey);
			}
			else if (m_bridges.find(secondKey) != m_bridges.end())
			{
				bridgeKeyList.push_back(secondKey);
			}

		}
	}

	return bridgeKeyList;
}

bool Board::FindObstacleBridge(const Position& firstPos, const Position& secondPos) const
{
	uint16_t lowerRowIndex{ std::min(firstPos.GetRow(), secondPos.GetRow()) };
	uint16_t lowerColumnIndex{ std::min(firstPos.GetColumn(), secondPos.GetColumn()) };
	uint16_t absRowValue = abs(firstPos.GetRow() - secondPos.GetRow()) ;
	std::vector<int16_t> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
	std::vector<int16_t> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
	uint8_t rowAddition, columnAddition;
	if (absRowValue == 1)
	{
		rowAddition = 1, columnAddition = 2;
	}
	else
	{
		rowAddition = 2, columnAddition = 1;
	}
	for (uint16_t rowIndex{ lowerRowIndex }; rowIndex <= lowerRowIndex + rowAddition; ++rowIndex)
	{
		for (uint16_t columnIndex{ lowerColumnIndex }; columnIndex <= lowerColumnIndex + columnAddition; ++columnIndex)
		{
			if (m_matrix[rowIndex][columnIndex] != nullptr)
			{
				for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
				{
					int16_t secondRowIndex{ rowIndex + rowDirection[directionIndex] };
					int16_t secondColumnIndex{ columnIndex + columnDirection[directionIndex] };
					if (!ValidPosition(secondRowIndex, secondColumnIndex))
					{
						continue;
					}
					if (m_matrix[secondRowIndex][secondColumnIndex] != nullptr)
					{
						if (m_matrix[secondRowIndex][secondColumnIndex]->GetPlayer() ==
							m_matrix[rowIndex][columnIndex]->GetPlayer())
						{
							Position bridge2FirstPosition(rowIndex, columnIndex);
							Position bridge2SecondPosition(secondRowIndex, secondColumnIndex);
							IColumnPtr bridge1FirstColumn{ m_matrix[firstPos.GetRow()][firstPos.GetColumn()] };
							IColumnPtr bridge1SecondColumn{ m_matrix[secondPos.GetRow()][secondPos.GetColumn()] };
							IColumnPtr bridge2FirstColumn{ m_matrix[rowIndex][columnIndex] };
							IColumnPtr bridge2SecondColumn{ m_matrix[secondRowIndex][secondColumnIndex] };
							if (bridge1FirstColumn == bridge2FirstColumn || bridge1FirstColumn == bridge2SecondColumn ||
								bridge1SecondColumn == bridge2FirstColumn || bridge1SecondColumn == bridge2SecondColumn)
							{
								continue;
							}
							
							if (BridgeExists(bridge2FirstPosition, bridge2SecondPosition))
							{
								if (doIntersect(firstPos, secondPos,
									bridge2FirstPosition, bridge2SecondPosition))
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool Board::Orientation(const Position& A, const Position& B, const Position& C) const
{
	int16_t val{ (B.GetColumn() - A.GetColumn()) * (C.GetRow() - B.GetRow()) -
		(B.GetRow() - A.GetRow()) * (C.GetColumn() - B.GetColumn()) };

	return (val > 0) ? 0 : 1; // 0 - left, 1 - right
}

bool Board::doIntersect(const Position& A1, const Position& B1, const Position& A2, const Position& B2) const
{
	bool o1{ Orientation(A1, B1, A2) };
	bool o2{ Orientation(A1, B1, B2) };
	bool o3{ Orientation(A2, B2, A1) };
	bool o4{ Orientation(A2, B2, B1) };

	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}

bool Board::ValidBridge(const Position& firstPos, const Position& secondPos) const
{
	if (BridgeExists(firstPos, secondPos)) return false;

	uint16_t absRowValue = abs(firstPos.GetRow() - secondPos.GetRow()) ;
	uint16_t absColumnValue = abs(firstPos.GetColumn() - secondPos.GetColumn()) ;
	IColumnPtr firstColumn{ m_matrix[firstPos.GetRow()][firstPos.GetColumn()] };
	IColumnPtr secondColumn{ m_matrix[secondPos.GetRow()][secondPos.GetColumn()] };

	if (std::shared_ptr<Column> firstColumnToVerify = std::dynamic_pointer_cast<Column> (firstColumn))
	{
		if (std::shared_ptr<Column> secondColumnToVerify = std::dynamic_pointer_cast<Column> (secondColumn))
		{
			if (firstColumn == nullptr || secondColumn == nullptr)
			{
				return false;
			}
			else if (firstColumn->GetPlayer() != secondColumn->GetPlayer())
			{
				return false;
			}
			if (absRowValue == 0 || absColumnValue == 0)
			{
				return false;
			}
			if (absRowValue + absColumnValue == 3)
			{
				if (FindObstacleBridge(firstPos, secondPos))
				{
					return false;
				}
				return true;
			}
		}
	}
	return false;
}

bool Board::ValidPosibleBridge(const Position& firstPos, const Position& secondPos) const
{
	uint16_t absRowValue = abs(firstPos.GetRow() - secondPos.GetRow());
	uint16_t absColumnValue = abs(firstPos.GetColumn() - secondPos.GetColumn());

	if (absRowValue == 0 || absColumnValue == 0)
	{
		return false;
	}
	if (absRowValue + absColumnValue == 3)
	{
		if (FindObstacleBridge(firstPos, secondPos))
		{
			return false;
		}
		return true;
	}
	return false;
}

const std::string Board::MakeKey(const Position& firstPos, const Position& secondPos) const
{
	const auto& row1{ firstPos.GetRow() },
		      & row2{ secondPos.GetRow() };
	const auto& column1{ firstPos.GetColumn() },
		      & column2{ secondPos.GetColumn() };

	std::string key{ std::to_string(row1) + " " + std::to_string(column1) +
		" " + std::to_string(row2) + " " + std::to_string(column2) };
	return std::move(key);
}

const std::pair<Position, Position> Board::ExtractPositionFromKey(const std::string& key) const
{
	std::istringstream in(key);
	uint16_t row, column;
	in >> row >> column;
	Position firstPosition(row, column);

	in >> row >> column;
	Position secondPosition(row, column);

	return std::move(std::make_pair(firstPosition, secondPosition));
}

void Board::MarkPathWithOnes(const Position& startPosition, std::vector<std::vector<bool>>* playerPath)
{
	std::array<int16_t, 8> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
	std::array<int16_t, 8> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
	std::stack<Position> positionStack;
	positionStack.push(startPosition);
	while (!positionStack.empty())
	{
		Position currentPosition = positionStack.top();
		positionStack.pop();
		bool modifiedMatrix = false;
		for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
		{
			int16_t nextPositionRow = currentPosition.GetRow() + rowDirection[directionIndex];
			int16_t nextPositionColumn = currentPosition.GetColumn() + columnDirection[directionIndex];
			if (ValidPosition(nextPositionRow, nextPositionColumn))
			{
				Position nextPosition(nextPositionRow, nextPositionColumn);
				if (BridgeExists(currentPosition, nextPosition))
				{
					if ((*playerPath)[nextPositionRow][nextPositionColumn] == 1)
					{
						(*playerPath)[currentPosition.GetRow()][currentPosition.GetColumn()] = 1;
						modifiedMatrix = true;
						continue;
					}
					positionStack.push(nextPosition);
				}
			}
		}
		if (!modifiedMatrix)
		{
			break;
		}
	}
}

void Board::ComputePathToWin(bool player, bool action, const Position& firstPos, const Position& secondPos)
{
	std::vector<std::vector<bool>>* playerPath{ nullptr };
	if (player == 0)
	{
		playerPath = &m_firstPlayerPath;
	}
	else
	{
		playerPath = &m_secondPlayerPath;
	}
	if (action == 0)
	{
		if (firstPos.GetRow() == 0 || firstPos.GetColumn() == 0)
		{
			(*playerPath)[firstPos.GetRow()][firstPos.GetColumn()] = 1;
		}
		else if (secondPos.GetRow() == 0 || secondPos.GetColumn() == 0)
		{
			(*playerPath)[secondPos.GetRow()][secondPos.GetColumn()] = 1;
		}

		if ((*playerPath)[firstPos.GetRow()][firstPos.GetColumn()] == 0)
		{
			MarkPathWithOnes(firstPos, playerPath);
		}
		if ((*playerPath)[secondPos.GetRow()][secondPos.GetColumn()] == 0)
		{
			MarkPathWithOnes(secondPos, playerPath);
		}
	}
	else
	{
		std::array<int16_t, 8> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
		std::array<int16_t, 8> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
		playerPath->clear();
		for (uint16_t index{ 0 }; index < m_matrix.size(); ++index)
		{
			playerPath->push_back(std::vector<bool>(m_matrix.size(), 0));
		}
		if (player == 0)
		{
			for (uint16_t index{ 0 }; index < m_matrix.size(); ++index)
			{
				if (m_matrix[0][index] != nullptr)
				{
					(*playerPath)[0][index] = 1;
					for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
					{
						int16_t nextPositionRow = rowDirection[directionIndex];
						int16_t nextPositionColumn = index + columnDirection[directionIndex];
						if (ValidPosition(nextPositionRow, nextPositionColumn))
						{
							Position nextPosition(nextPositionRow, nextPositionColumn);
							Position currentPosition(0, index);
							if (BridgeExists(currentPosition, nextPosition))
							{
								if ((*playerPath)[nextPositionRow][nextPositionColumn] == 0)
								{
									MarkPathWithOnes(nextPosition, playerPath);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			for (uint16_t index{ 0 }; index < m_matrix.size(); ++index)
			{
				if (m_matrix[index][0] != nullptr)
				{
					(*playerPath)[index][0] = 1;
					for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
					{
						int16_t nextPositionRow = index + rowDirection[directionIndex];
						int16_t nextPositionColumn = columnDirection[directionIndex];
						if (ValidPosition(nextPositionRow, nextPositionColumn))
						{
							Position nextPosition(nextPositionRow, nextPositionColumn);
							Position currentPosition(index, 0);
							if (BridgeExists(currentPosition, nextPosition))
							{
								if ((*playerPath)[nextPositionRow][nextPositionColumn] == 0)
								{
									MarkPathWithOnes(nextPosition, playerPath);
								}
							}
						}
					}
				}
			}
		}
	}
}

bool Board::CheckWinner(bool player) const
{
	if (player == 0)
	{
		for (uint16_t columnIndex{ 0 }; columnIndex < m_matrix.size(); ++columnIndex)
		{
			if (m_firstPlayerPath[m_matrix.size() - 1][columnIndex] == 1)
			{
				return true;
			}
		}
	}
	else
	{
		for (uint16_t rowIndex{ 0 }; rowIndex < m_matrix.size(); ++rowIndex)
		{
			if (m_secondPlayerPath[rowIndex][m_matrix.size() - 1] == 1)
			{
				return true;
			}
		}
	}
	return false;
}

uint16_t Board::RemoveColumn(const Position& position)
{
	uint16_t bridgesDeleted = 0;
	const auto& bridgesToDelete = GetColumnConnections(position);

	std::ranges::for_each(bridgesToDelete, [&](const std::string& key) { 
		m_bridges.erase(key);
		++bridgesDeleted;
		});

	m_matrix[position.GetRow()][position.GetColumn()] = nullptr;

	return bridgesDeleted;
	
}

const IColumnPtr Board::GetElement(const Position& position) const
{
	return m_matrix[position.GetRow()][position.GetColumn()];
}

const IColumnPtr Board::GetElement(const uint16_t& row, const uint16_t& column) const
{
	return m_matrix[row][column];
}

const BridgeVector Board::GetBridgesPositions() const
{
	std::regex pattern{R"(\b\d+)"};
	BridgeVector bridgesPositions;
	for (auto& bridge : m_bridges)
	{
		std::vector<uint16_t> positions;
		auto string{ bridge.first };
		auto it{ std::sregex_iterator(string.begin(), string.end(), pattern) };
		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}
		Position firstColumn{positions[0], positions[1]};
		Position secondColumn{ positions[2], positions[3] };
		bridgesPositions.emplace_back(std::move(firstColumn), std::move(secondColumn));
	}
	return std::move(bridgesPositions);
}

const uint16_t Board::GetSize() const 
{
	return std::move((uint16_t)m_matrix.size());
}

bool Board::PlaceColumn(const Position& position, IPlayerPtr player)
{
	auto columnOnPosition = GetElement(position);
	if (columnOnPosition&& columnOnPosition->GetPlayer()->GetColor() == EColor::NoColor) return true;
	if (ValidPlaceColumn(position)) {
		IColumnPtr newColumn{ std::make_shared<Column>(player) };
		m_matrix[position.GetRow()][position.GetColumn()] = newColumn ;

		return true;
	}
	return false;
}

bool Board::PlaceColumn(const Position& position, IColumnPtr column)
{
	if (ValidPlaceColumn(position)) {
		m_matrix[position.GetRow()][position.GetColumn()] = column;

		return true;
	}
	return false;
}

bool Board::MakeBridge(const Position& firstPos, const Position& secondPos, IPlayerPtr player)
{
	if (ValidBridge(firstPos, secondPos)) {
		Bridge* bridge{ new Bridge(m_matrix[firstPos.GetRow()][firstPos.GetColumn()],
			m_matrix[secondPos.GetRow()][secondPos.GetColumn()]) };
		std::string key{ MakeKey(firstPos, secondPos) };
		m_bridges.emplace(key, bridge);

		return true;
	}
	return false;
}

bool Board::RemoveBridge(const Position& firstPos, const Position& secondPos, IPlayerPtr player)
{
	if (!BridgeExists(firstPos, secondPos)) 
		return false;

	const auto firstKey{ MakeKey(firstPos, secondPos) };
	const auto secondKey{ MakeKey(secondPos, firstPos) };
	if (m_bridges.find(firstKey) != m_bridges.end())
	{
		m_bridges.erase(firstKey);
	}
	else
	{
		m_bridges.erase(secondKey);
	}
	return true;
}

void Board::Clear()
{
	m_matrix = std::vector{ GetSize(), std::vector<IColumnPtr>{GetSize(), nullptr} };
	m_bridges.clear();
	m_firstPlayerPath = std::vector{ GetSize(), std::vector<bool>(GetSize(), 0) };
	m_secondPlayerPath = std::vector{ GetSize(), std::vector<bool>(GetSize(), 0) };
}

bool Board::BridgeExists(const Position& firstPos, const Position& secondPos) const
{
	const auto firstKey{ MakeKey(firstPos, secondPos) };
	const auto secondKey{ MakeKey(secondPos, firstPos) };
	if (m_bridges.find(firstKey)  != m_bridges.end() ||
		m_bridges.find(secondKey) != m_bridges.end()) return true;
	return false;
}

const IColumnPtr Board::operator[](Position pos) const
{
	return GetElement(pos);
}

bool Board::operator==(const Board& rhs) const
{
	for (uint16_t line{ 0 }; line < m_matrix.size(); ++line)
	{
		for (uint16_t column{ 0 }; column < m_matrix[line].size(); ++column)
		{
			if (m_matrix[line][column]->GetPlayer() != rhs.m_matrix[line][column]->GetPlayer())
			{
				return false;
			}
		}
	}
	if (m_bridges.size() != rhs.m_bridges.size())
	{
		return false;
	}
	for (const auto& [key, bridge] : m_bridges)
	{
		auto positions = ExtractPositionFromKey(key);
		auto key1ToVerify = MakeKey(positions.first, positions.second);
		auto key2ToVerify = MakeKey(positions.second, positions.first);
		if (!rhs.m_bridges.contains(key1ToVerify) && rhs.m_bridges.contains(key2ToVerify))
		{
			return false;
		}
	}
	return true;
}