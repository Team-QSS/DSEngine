#pragma once

namespace DS
{
	class BaseGame
	{
	public:
		BaseGame() = default;
		virtual ~BaseGame() = default;

		void initialize();
		void update();
		void draw();
		void destroy();

		virtual void onInitialize() = 0;
		virtual void onUpdate() = 0;
		virtual void onDraw() = 0;
		virtual void onDestroy() = 0;

	protected:

	private:
		BaseGame & operator=(const BaseGame&) = delete;
		BaseGame & operator=(BaseGame&&) = delete;
		BaseGame(const BaseGame &) = delete;
		BaseGame(BaseGame &&) = delete;
	};
}