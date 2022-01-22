#pragma once

namespace ts
{
	class Template
	{
	public:
		Template(int x, int y, float z, float t);

		~Template();

		void Move();

		void SetSomething(int something);

	private:
		int secret;
	};
}
