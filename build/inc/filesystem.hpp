// Create a folder in directory
bool createFolder(std::filesystem::path directory){
    if (std::filesystem::create_directory(directory)) {
        ConsoleWrite("[ FileSys ] Folder created successfully.");
        return true;
    } else {
        ConsoleWrite("[ FileSys - ERROR ] Failed to create folder.");
        return false;
    }
}

// Create a file with a given name plus extension
bool createFile(std::filesystem::path location = "../saves/", std::filesystem::path file = "save_game", std::filesystem::path extension = "txt"){
    std::filesystem::path tempFile = "";
    tempFile += location;
    tempFile += file;
    tempFile += ".";
    tempFile += extension;
    std::ofstream MyFile(tempFile);
    ConsoleWrite("[ FileSys ] File created successfully.");
    return true;
}

// count folders in a directory
int countFolders(const std::string& directoryPath) {
    int folderCount = 0;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (std::filesystem::is_directory(entry.path())) {
            folderCount++;
        }
    }

    return folderCount;
}

// return folder names in given directory
std::vector<std::string> getFolderNames(std::string directoryPath){
    std::vector<std::string> folderNames;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (std::filesystem::is_directory(entry.path())) {
                folderNames.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    return folderNames;
}

// delete a folder and it's contents in given directory
void DeleteFolder(std::filesystem::path path){
    std::filesystem::remove_all(path);
    ConsoleWrite("[ FileSys ] Deleted save game\n");
}
