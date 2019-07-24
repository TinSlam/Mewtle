#pragma once

namespace Mewtle{
	class Event{
		private :
			int id = 0;
			std::string* name = nullptr;
			bool cancelled = false;

		public :
			Event(int id, std::string* name);
			~Event();

			virtual bool perform() = 0;
			void setCancelled(bool value);
	};
}
