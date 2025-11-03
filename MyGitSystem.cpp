// mygit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
int mygit_init();
int mygit_hash_object(char* argv[]);
int mygit_cat_file();

int main(int argc, char* argv[])
{
    if (argc < 2)
	{
		std::cout << "\n(En) Warning: You need to give an argument!\n(Tr) Uyari: Bir komut girmelisiniz!\n";
		return 1;
    }

	string fcommand = argv[1];

	if (fcommand == "init")
	{
		mygit_init();
	}
	else if (fcommand == "list-args")
	{
		for (int i = 0; i < argc; i++) {
			std::cout << "Argument " << i << ": " << argv[i] << "\n";
		}
	}
	else if (fcommand == "cat-file")
	{
		std::cout << "cat-file command selected\n";
	}
	else if (fcommand == "hash-object")
	{
		mygit_hash_object(argv);
	}
	else
	{
		std::cout << "\n(En) Warning: Unknown command!\n(Tr) Uyari: Bilinmeyen komut!\n";
		return 1;
	}


}

int mygit_init() { // Initializes a mygit repository in the current directory

	std::cout << "\n(En) Initiliazing mygit repository... (Tr) Git deposu baslatiliyor... \n";

	try {
		std::filesystem::current_path();

		std::cout << "(En) Current path: (Tr) Gecerli dizin: " << std::filesystem::current_path() << "\n";

		std::filesystem::create_directory(".mygit");
		std::filesystem::create_directory(".mygit/objects");
		std::filesystem::create_directory(".mygit/refs");
		std::filesystem::create_directory(".mygit/refs/heads");
		std::filesystem::create_directory(".mygit/refs/tags");

		std::ofstream headFile(".mygit/HEAD"); // This method authomatically creates the file if it does not exist

		if (headFile.is_open()) {
			headFile << "ref: refs/heads/main\n"; // This file points to the current branch and default is main
			headFile.close();
			std::cout << "(En) HEAD file created! (Tr) HEAD dosyasi olusturuldu!\n";
		}
		else {
			std::cout << "(En) Error: Could not create HEAD file! (Tr) Hata: HEAD dosyasi olusturulamadi!\n";
			return 1;
		}

		std::cout << "(En) Repository initialized! (Tr) Git deposu baslatildi!\n";
	}
	catch (const std::filesystem::filesystem_error) {
		std::cout << "(En) Error: While creating git repos an file error accured! (Tr) Hata: Git deposu baslatilirken bir dosya hatasi alindi!\n";
		return 1;
	}
	catch (...) {
		std::cout << "(En) Error: Unknown error accured while creating git repo! (Tr) Hata: Git deposu baslatilirken bilinmeyen bir hata alindi!\n";
		return 1;
	}
	return 0;
}

int mygit_hash_object(char* argv[]) { // Hashes a file and stores it in the objects directory

	if (argv[2] == nullptr) {
		std::cout << "\n(En) Usage: mygit hash-object [-t <type>] [-w] [--path=<file>}\n(Tr) Kullanım: mygit hash-object [-t <tip>] [-w] [--path=<tip>]\n";
		std:cout << "(En) Types: commit,tree,blob and tag. Default: blob\n(Tr) Tipler: commit,tree,blob and tag. Varsayılan: blob\n";
		return 1;
	}

	string commandOption = argv[2];

	if (commandOption != "--help" && commandOption != "-w" && commandOption != "-t" && commandOption.find("--path=") == string::npos) {
		std::cout << "\n(En) Warning: Unknown option!\n(Tr) Uyari: Bilinmeyen secenek!\n";
		return 1;
	}


	if (commandOption == "--help")
	{
		std::cout << "\n(En) Usage: mygit hash-object [-t <type>] [-w] [--path=<file>}\n(Tr) Kullanim: mygit hash-object [-t <tip>] [-w] [--path=<tip>]\n";
		std::cout << "(En) Types: commit,tree,blob and tag. Default: blob\n(Tr) Tipler: commit,tree,blob and tag. Varsayılan: blob\n";
		return 0;
	}
	else if (commandOption.find("--path=") != string::npos)
	{
		string filePath = commandOption.substr(7); // Extract the file path from the argument
		std::cout << "(En) File path: " << filePath << "\n(Tr) Dosya yolu: " << filePath << "\n";

	}
	else if (commandOption == "-t")
	{
		if (argv[3] == nullptr) {
			std::cout << "\n(En) Warning: You need to give a type after -t option!\n(Tr) Uyari: -t seceneginden sonra bir tip girmeniz gerekiyor!\n";
			return 1;
		}
		string typeOption = argv[3];
		if (typeOption != "commit" && typeOption != "tree" && typeOption != "blob" && typeOption != "tag") {
			std::cout << "\n(En) Warning: Unknown type!\n(Tr) Uyari: Bilinmeyen tip!\n";
			return 1;
		}
		std::cout << "(En) Type option selected: " << typeOption << "\n(Tr) Tip secenegi secildi: " << typeOption << "\n";
	}
	else if (commandOption == "-w") {
		std::cout << "(En) Write option selected\n(Tr) Yazma secenegi secildi\n";
	}
	std::cout << "hash-object command selected\n";
	return 0;
}

int mygit_cat_file() { // Displays the content of a hashed object
	return 0;
}