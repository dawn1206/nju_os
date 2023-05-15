#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
// #include <memory>
using namespace std;
namespace fs = std::filesystem;

class tiny_process {
private:
  const int pid;
  const string p_name;
  // unique_ptr<tiny_process> parent_process;
  tiny_process *pprocess;
  vector<tiny_process *> subprocess;

public:
  tiny_process(const int pid, const string p_name, tiny_process *pp)
      : pid(pid), p_name(p_name), pprocess(pp) {}
  int print_subprocess();
  void add_subprocess(tiny_process *sp);
  void set_pprocess(tiny_process *pp);
  vector<tiny_process *> get_subprocess() { return this->subprocess; }
  tiny_process get_pprocess() { return *(this->pprocess); }
};

int tiny_process::print_subprocess() {
  int count = 1;
  for (const auto &sp : this->subprocess) {
    count += sp->print_subprocess();
    for (int i = 0; i < count; i++)
      cout << "|" << endl;
    count = 1;
  }
}
void tiny_process::set_pprocess(tiny_process *pp) {
  if (pp != nullptr)
    this->pprocess = pp;
  else {
    cout << "what is wrong with this pp" << endl;
  }
}
void tiny_process::add_subprocess(tiny_process *sp) {
  if (sp != nullptr)
    this->subprocess.push_back(sp);
  else {
    cout << "what is wrong with this sp" << endl;
  }
}

void print_version() {
  cout << "pstree (PSmisc) UNKNOWN \n Copyright (C) 1993-2019 Werner "
          "Almesberger and Craig Small\nPSmisc comes with ABSOLUTELY NO "
          "WARRANTY.This is free software,\nand you are welcome to "
          "redistribute it under the terms of the GNU\nGeneral Public "
          "License.For more information about these matters,\nsee the files "
          "named COPYING."
       << endl;
}

int find_id(string ori_file, string filed, int field_capacity) {

  int position = ori_file.find(filed);

  string sub_field =
      ori_file.substr(position + int(filed.size()) + 1, field_capacity);

  int enter_signal = sub_field.find("\n");
  try {
    int id = stoi(sub_field.substr(0, enter_signal));
    return id;
  } catch (std::invalid_argument const &ex) {
    cout << sub_field.substr(0, enter_signal) << endl;
    return -1;
  } catch (std::out_of_range const &ex) {
    cout << sub_field.substr(0, enter_signal) << endl;
    return -1;
  }
}

int main(int argc, char *argv[]) {
  string folderPath = "/proc"; // 替换为你要读取的文件夹路径
  unordered_map<string, int> arg_map{{"-p", 0}, {"-n", 0}, {"-V", 0}};

  for (auto arg : std::vector<char *>(argv, argv + argc)) {
    arg_map[arg]++;
  }

  if (arg_map["-V"] > 0) {
    print_version();
    return 0;
  } else {

    for (const auto &entry : fs::directory_iterator(folderPath)) {
      try {
        if (entry.is_directory()) {
          const int pid = stoi(entry.path().filename());
          auto proc = entry.path() / ("status");
          ifstream file(proc);
          if (file) {
            stringstream buffer;
            buffer << file.rdbuf();
            string fileContents = buffer.str();
            const int pid = find_id(fileContents, "Pid", 5);
            const int ppid = find_id(fileContents, "PPid", 5);

            cout << "文件名：" << proc << endl;
            cout << "文件内容：" << pid << endl;
            cout << "文件内容：" << ppid << endl << endl;
          } else {
            cerr << "无法打开文件：" << proc << endl;
          }
          proc = (entry.path()/"task")/(to_string(pid))/"children";
          
        }
      } catch (std::invalid_argument const &ex) {
        continue;
      } catch (std::out_of_range const &ex) {
        continue;
      }
    }
  }

  return 0;
}
