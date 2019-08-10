#pragma once

namespace Mewtle{
	class Material{
		private :
			GLuint* materials = nullptr;
			int materialCount = 0;
			int* materialsIndices = nullptr;

			static std::vector<Material*> allMaterials;

		public :
			Material(std::map<int, std::string>* materialsPath, std::string directoryPath, GLuint* materials, int materialCount, int* materialsIndices);
			~Material();

			GLuint* getMaterials();
			int getMaterialCount();
			int getMatLength(int index);
			int getMatStartIndex(int index);

			static void deleteMaterials();
	};
}
