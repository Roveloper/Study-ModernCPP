#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
  for (auto it = m.begin(); it != m.end(); ++it){
    std::cout << it->first << " -> " << it->second << std::endl;
  }

  for (const auto& val : m) { // val은 std::pair로 전달됨
    std::cout << val.first << " -> " << val.second << std::endl;
  }
}

int main() {
  std::map<std::string, int> lck_teams; // key, value의 타입을 각각 지정

  // pair로 만들어서 전달하거나, make_pair로 전달, 또는 그냥 입력하면 없는 경우 채워짐
  lck_teams.insert(std::pair<std::string, int>("T1", 1));
  lck_teams.insert(std::pair<std::string, int>("DK", 2));
  lck_teams.insert(std::pair<std::string, int>("Gen G", 3));
  lck_teams.insert(std::pair<std::string, int>("KT", 4));
  lck_teams.insert(std::pair<std::string, int>("LSB", 5));
  lck_teams.insert(std::pair<std::string, int>("HLE", 6));

  lck_teams.insert(std::make_pair("KDF", 7));
  lck_teams.insert(std::make_pair("BRO", 8));

  lck_teams["NS"] = 9;
  lck_teams["DRX"] = 10;

  print_map(lck_teams);

  if (lck_teams.find("T1") != lck_teams.end()) {
    std::cout << "T1의 순위는 ? :: " << lck_teams["T1"] << std::endl;
  }

  
  if (lck_teams.find("EDG") != lck_teams.end()) {
    std::cout << "EDG의 순위는 ? :: " << lck_teams["EDG"] << std::endl;
  }

  std::cout << "EDG의 순위는 ? :: " << lck_teams["EDG"] << std::endl; // 주의할 것 (map의 경우 값이 없으면, 기본 생성자를 호출해서 return하므로, 값이 없어도 뭔가 튀어 나옴)
  // 또한 insert를 이용해서는 중복된 값을 넣을 수 없음 (값도 바뀌지 않음)
  std::map<int, int> test;
  test.insert(std::make_pair(1, 10));
  test.insert(std::make_pair(1, 15));
  print_map(test);
  test[1] = 15; // 바꾸려면 이렇게 바꿔야함
  print_map(test); 

}