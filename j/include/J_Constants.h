#pragma once
#include <string>

namespace j_constants {

// Constants
constexpr int gScreenWidth{640};
constexpr int gScreenHeight{480};

// PATH TO YOUR RESOURCE FOLDER 'resources', 'gResPath'
const std::string gResPath{"./j/resources/"};

// PATH'S TO ALL YOUR EXTERNAL RESOURCES using 'gResPath'
const std::string bg_str{gResPath + "images/bg.png"};
const std::string player_str{gResPath + "images/player.png"};
const std::string orb_str{gResPath + "images/orb.png"};
const std::string pipe_str{gResPath + "images/pipe.png"};

} // namespace j_constants
