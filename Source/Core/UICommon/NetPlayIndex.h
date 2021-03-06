// Copyright 2019 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <map>
#include <optional>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "Common/Flag.h"

struct NetPlaySession
{
  std::string name;
  std::string region;
  std::string method;
  std::string server_id;
  std::string game_id;
  std::string version;

  int player_count;
  int port;

  bool has_password;
  bool in_game;

  bool EncryptID(const std::string& password);
  std::optional<std::string> DecryptID(const std::string& password) const;
};

class NetPlayIndex
{
public:
  explicit NetPlayIndex();
  ~NetPlayIndex();

  std::optional<std::vector<NetPlaySession>>
  List(const std::map<std::string, std::string>& filters = {});

  static std::vector<std::pair<std::string, std::string>> GetRegions();

  bool Add(NetPlaySession session);
  void Remove();

  void SetPlayerCount(int player_count);
  void SetInGame(bool in_game);
  void SetGame(std::string game);

  const std::string& GetLastError() const;

private:
  void NotificationLoop();

  Common::Flag m_running;

  std::string m_secret;
  std::string m_game;
  int m_player_count = 0;
  bool m_in_game = false;

  std::string m_last_error;
  std::thread m_session_thread;
};
