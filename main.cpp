#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

/*!
 @brief Lambda is a function for creating a list of files with a specified file name extension.
 @param path the directory where to perform a recursive search.
 @param extension the specified file name extension.
*/
auto recursiveGetFileNamesByExtension =
       [](const std::filesystem::path & path,
          const std::string & extension)
{
    std::vector<std::string> listResult;

    // clearing lists
    listResult.clear();
    // recursive traversal of files and folders
    for(auto & p: std::filesystem::recursive_directory_iterator(path)) {
        // for the lambda function test
        std::cout << p.path() << '\n';

        // path analysis

        // if it is a file
        if(p.is_regular_file()) {
            // and it has a given extension
            if(!p.path().extension().compare(extension)) {
                // then add to the result list
                listResult.push_back(p.path().generic_string());
            }
        }
    }

    // returning the result
    return std::make_unique<std::vector<std::string>>(listResult);
};

/*!
 @brief A subroutine for printing list items with a title.
 @param inList the original list.
 @param inTitle the title of the list.
*/
void print(const std::vector<std::string> & inList, const std::string & inTitle)
{
    std::cout
        << inTitle << ":\n"
        << "---------------- begin ------------------\n";
    for (const auto & elem : inList)
        std::cout << elem << std::endl;
    std::cout
        << "---------------- end --------------------\n";
}

/*!
 @brief The lambda function testing routine.
 @param path the directory where to perform a recursive search.
 @param extension the specified file name extension.
*/
auto recursiveGetFileNamesByExtension_test(
    const std::filesystem::path & path,
    const std::string & extension)
{
    std::cout
        << "List of all files:\n"
        << "---------------- begin ------------------\n";
    auto result = recursiveGetFileNamesByExtension(path, extension);
    std::cout
        << "---------------- end --------------------\n";
    
    return result;
}

int main()
{
    // directory path and file extension
    const std::filesystem::path path = "D:\\dir1";
    const std::string extension = ".txt";

    // calling the lambda function testing routine
    auto result = recursiveGetFileNamesByExtension_test(path, extension);

    // output of the result
    print(*result, "\nList of found files by template '*" + extension + "'");

    // program shutdown
    return 0;
}
