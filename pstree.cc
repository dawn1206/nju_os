#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

class tiny_process {
private:
  const int pid;
  const string p_name;
  bool is_root = true;
  tiny_process *pprocess;
  vector<tiny_process *> subprocess;

public:
  tiny_process(const int pid, const string p_name, tiny_process *pp)
      : pid(pid), p_name(p_name), pprocess(pp) {}
  int print_subprocess();
  void add_subprocess(tiny_process *sp);
  int get_ppid() const {
    return (this->pprocess == nullptr) ? -1 : this->pprocess->pid;
  }
  int get_pid() const { return this->pid; }
  bool root() { return this->is_root; }
  void set_pprocess(tiny_process *pp);
  tiny_process *get_pprocess() { return (this->pprocess); }
  void print_process_tree(const std::string &prefix, bool is_last) const;

  tiny_process(const tiny_process &) = delete;            // 禁用复制构造
  tiny_process &operator=(const tiny_process &) = delete; // 禁用复制赋值
  tiny_process(tiny_process &&) = default;                // 启用移动构造
  tiny_process &operator=(tiny_process &&) = default;     // 启用移动赋值
};

void tiny_process::print_process_tree(const std::string& prefix, bool is_last) const {
  std::string new_prefix;

  // 当前进程的输出前缀
  if (is_last) {
    // 当前进程是最后一个子进程，使用"`─"前缀，并为后续行添加"  "前缀
    std::cout << prefix << "─" << this->p_name << "(" << this->pid << ")\n";
    new_prefix = prefix + "  ";
  } else {
    // 当前进程不是最后一个子进程，使用"├─"前缀，并为后续行添加"| "前缀
    std::cout << prefix << "├─" << this->p_name << "(" << this->pid << ")\n";
    new_prefix = prefix + "| ";
  }

  // 递归打印每个子进程
  for (size_t i = 0; i < this->subprocess.size(); ++i) {
    this->subprocess[i]->print_process_tree(new_prefix, i == this->subprocess.size() - 1);
  }
}



void tiny_process::set_pprocess(tiny_process *pp) {
  if (pp != nullptr) {
    this->pprocess = pp;
    this->is_root = false;
  } else {
    cout << "what is wrong with this pp" << endl;
  }
}
void tiny_process::add_subprocess(tiny_process *sp) {
  this->subprocess.push_back(sp);
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

template <typename T>
T find_field(const std::string &ori_file, const std::string &field,
             int field_capacity) {
  if constexpr (std::is_same_v<T, int>) {
    try {
      size_t position = ori_file.find(field);

      std::string sub_field =
          ori_file.substr(position + field.size() + 1, field_capacity);

      size_t enter_signal = sub_field.find("\n");
      std::string result = sub_field.substr(0, enter_signal);
      return std::stoi(result);
    } catch (const std::invalid_argument &ex) {
      std::cout << "invalid argument" << std::endl;
      return -1;
    } catch (const std::out_of_range &ex) {
      std::cout << "out of integer range" << std::endl;
      return -1;
    }
  } else if constexpr (std::is_same_v<T, std::string>) {
    size_t position = ori_file.find(field);

    std::string sub_field =
        ori_file.substr(position + field.size() + 2, ori_file.size());
    size_t enter_signal = sub_field.find("\n");
    std::string result = sub_field.substr(0, enter_signal);
    return result;
  }
}

int main(int argc, char *argv[]) {
  string folderPath = "/proc"; // 替换为你要读取的文件夹路径
  unordered_map<string, int> arg_map{{"-p", 0}, {"-n", 0}, {"-V", 0}};
  unordered_map<int, tiny_process *> process_map;

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
            const int pid = find_field<int>(fileContents, "Pid", 5);
            const int ppid = find_field<int>(fileContents, "PPid", 5);
            const string process_name =
                find_field<string>(fileContents, "Name", 5);

            process_map[pid] = new tiny_process(pid, process_name, nullptr);

            if (ppid != 0 && process_map.count(ppid)) {
              process_map[pid]->set_pprocess(process_map[ppid]);
            }
            //     cout << "文件名：" << proc << endl;
            //       cout << "pid：" << pid << endl;
            //           cout << "ppid: " << ppid << endl;
            //         cout << "name: " << process_name << endl << endl;

          } else {
            cerr << "无法打开文件：" << proc << endl;
          }
        }
      } catch (std::invalid_argument const &ex) {
        continue;
      } catch (std::out_of_range const &ex) {
        continue;
      }
    }
    cout << process_map.size() << endl;

    vector<int> root_pid;

    for (auto &kv : process_map) {
      tiny_process *proc = kv.second;
      int ppid = proc->get_ppid();

      if (process_map.count(ppid)) {
        process_map[ppid]->add_subprocess(kv.second);
      }
    }
    cout << process_map.size() << endl;
  }
  for (const auto &kv : process_map) {
    tiny_process *proc = kv.second;
    if (proc->root()) {
      proc->print_process_tree("",true);
      std::cout << "\n";
    }
  }
  return 0;
}
