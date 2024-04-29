export module TwixtParser;

export import "ITwixtParser.h";


export namespace parser
{
	class TwixtParser : public ITwixtParser
	{
	public:
		TwixtParser() = default;
		TwixtParser(const TwixtParser& other) = default;

		size_t LoadPTG(std::string_view path) override;
		bool SavePTG(std::string_view path) override;

		void AddColumn(const Position& position) override;
		void AddBridge(bool removed, const Position& firstPos, const Position& secondPos) override;

		PTGGameRepresentation GetGamePreview(int historyIndex) const override;

		void Clear() override;

		static bool HasExtension(const std::string_view filePath, const std::string_view extension);


	private:
		PTGGameRepresentation m_representation;

	};
}

