#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>

namespace fs = boost::filesystem;

boost::mutex mutex;

std::string file_directory, file_res;

void task_thread(std::string file_path) {
    mutex.lock();
    fs::ifstream ifs;
    fs::ofstream ofs;
    ifs.open(file_path, std::ios::in);
    ofs.open(file_res, std::ios::app);
    std::vector<std::string> Buff;
    if (ifs.is_open() && ofs.is_open()) {
        {
            std::string str, buf, file_delim;
            ifs >> str;
            int i = 0;
            while (getline(ifs, buf))
            {
                 if(i > 0)file_delim += buf;
                 i++;
            }
            boost::split(Buff, str, boost::is_any_of(file_delim));
            std::string fname = file_path.substr(file_path.find_last_of("\\")+1, std::string::npos);
            ofs << "[" + fname + "]" << std::endl;
            for(unsigned int i = 0; i < Buff.size(); i++){
                ofs << Buff[i] << std::endl;
            }
        }
        ofs.close();
        ifs.close();
    }
    else {
        std::cout << "Error!" << std::endl;
    }
    mutex.unlock();
}

void pars_file_thread() {
    boost::thread_group threads;
    for (fs::directory_iterator it(file_directory); it != fs::directory_iterator(); ++it) {
       if (it->path().extension() == ".txt") {
           std::string fpath = (it->path()).string();
           threads.create_thread(boost::bind(&task_thread, fpath));
      }
    }
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    threads.join_all();
}

int main() {
    std::cout << "Enter directory path:" << std::endl;
    std::cin >> file_directory;
    std::cout << "Enter the name and path of the file with the results (result.txt):" << std::endl;
    std::cin >> file_res;
    pars_file_thread();
    system("pause");
    return 0;
}

