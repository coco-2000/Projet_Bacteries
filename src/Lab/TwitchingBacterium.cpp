#include "TwitchingBacterium.hpp"
#include "Application.hpp"

j::Value const& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

Bacterium* TwitchingBacterium::clone() const
{
    return new TwitchingBacterium(*this);
}

