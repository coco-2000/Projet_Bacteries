#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
// window
Config::Config(std::string path) : mConfig(j::readFromFile(path))
, simulation_debug(mConfig["debug"].toBool())
, window_simulation_width(mConfig["window"]["simulation"]["width"].toDouble())
, window_simulation_height(mConfig["window"]["simulation"]["height"].toDouble())
, window_stats_width(mConfig["window"]["stats"]["width"].toDouble())
, window_title(mConfig["window"]["title"].toString())
, window_antialiasing_level(mConfig["window"]["antialiasing level"].toInt())

// stats
, stats_refresh_rate(mConfig["stats"]["refresh rate"].toDouble())

// simulation

, simulation_time_factor(mConfig["simulation"]["time"]["factor"].toDouble())
, simulation_fixed_step(mConfig["simulation"]["time"]["fixed step"].toDouble())
, simulation_time_max_dt(sf::seconds(mConfig["simulation"]["time"]["max dt"].toDouble()))
, simulation_background(mConfig["simulation"]["background"].toString())
, simulation_debug_background(mConfig["simulation"]["debug background"].toString())
, simulation_size(mConfig["simulation"]["size"].toInt())

// petri dish
,petridish_min_gradient(mConfig["petri dish"]["gradient"]["exponent"]["min"].toDouble())
,petridish_max_gradient(mConfig["petri dish"]["gradient"]["exponent"]["max"].toDouble())
,petridish_delta_gradient(mConfig["petri dish"]["gradient"]["exponent"]["delta"].toDouble())

,petridish_min_temperature(mConfig["petri dish"]["gradient"]["exponent"]["min"].toDouble())
,petridish_max_temperature(mConfig["petri dish"]["gradient"]["exponent"]["min"].toDouble())
,petridish_default_temperature(mConfig["petri dish"]["temperature"]["default"].toDouble())
,petridish_delta_temperature(mConfig["petri dish"]["temperature"]["delta"].toDouble())

// generator
, generator_nutriment_delay(mConfig["generator"]["nutriment"]["delay"].toDouble())
, generator_nutriment_prob(mConfig["generator"]["nutriment"]["prob"].toDouble())

// nutriments
,nutrimentA_growth_speed(mConfig["nutriments"]["A"]["growth"]["speed"].toInt())
,nutrimentA_min_temperature(mConfig["nutriments"]["A"]["growth"]["min temperature"].toInt())
,nutrimentA_max_temperature(mConfig["nutriments"]["A"]["growth"]["max temperature"].toInt())
,nutrimentA_min_qty(mConfig["nutriments"]["A"]["quantity"]["min"].toInt())
,nutrimentA_max_qty(mConfig["nutriments"]["A"]["quantity"]["max"].toInt())

,nutrimentB_growth_speed(mConfig["nutriments"]["B"]["growth"]["speed"].toInt())
,nutrimentB_min_temperature(mConfig["nutriments"]["B"]["growth"]["min temperature"].toInt())
,nutrimentB_max_temperature(mConfig["nutriments"]["B"]["growth"]["max temperature"].toInt())
,nutrimentB_min_qty(mConfig["nutriments"]["B"]["quantity"]["min"].toInt())
,nutrimentB_max_qty(mConfig["nutriments"]["B"]["quantity"]["max"].toInt())
,nutrimentB_resistance_factor(mConfig["nutriments"]["B"]["resistance factor"].toDouble())
,nutrimentB_poison_factor(mConfig["nutriments"]["B"]["poison factor"].toDouble())
,nutrimentB_nutritive_factor(mConfig["nutriments"]["B"]["nutritive factor"].toDouble())

,poison_min_qty(mConfig["nutriments"]["poison"]["quantity"]["min"].toInt())
,poison_max_qty(mConfig["nutriments"]["poison"]["quantity"]["max"].toInt())
,poison_resistance_factor(mConfig["nutriments"]["poison"]["resistance factor"].toDouble())
,poison_toxic_factor(mConfig["nutriments"]["poison"]["toxic factor"].toDouble())

//bactéries
,simplebact_min_energy(mConfig["simple bacterium"]["energy"]["min"].toDouble())
,simplebact_max_energy(mConfig["simple bacterium"]["energy"]["max"].toDouble())
,simplebact_min_radius(mConfig["simple bacterium"]["radius"]["min"].toDouble())
,simplebact_max_radius(mConfig["simple bacterium"]["radius"]["max"].toDouble())
,simplebact_tumble_algo(mConfig["simple bacterium"]["tumble"]["algo"].toString())

,swarmbact_min_energy(mConfig["swarm bacterium"]["energy"]["min"].toDouble())
,swarmbact_max_energy(mConfig["swarm bacterium"]["energy"]["max"].toDouble())
,swarmbact_min_radius(mConfig["swarm bacterium"]["radius"]["min"].toDouble())
,swarmbact_max_radius(mConfig["swarm bacterium"]["radius"]["max"].toDouble())
,swarmbact_speed(mConfig["swarm bacterium"]["speed"]["initial"].toDouble())

,twitchingbact_min_energy(mConfig["twitching bacterium"]["energy"]["min"].toDouble())
,twitchingbact_max_energy(mConfig["twitching bacterium"]["energy"]["max"].toDouble())
,twitchingbact_min_radius(mConfig["twitching bacterium"]["radius"]["min"].toDouble())
,twitchingbact_max_radius(mConfig["twitching bacterium"]["radius"]["max"].toDouble())
,twitchingbact_speed_factor(mConfig["twitching bacterium"]["speed factor"].toDouble())
,twitchingbact_consumption_factor_move(mConfig["twitching bacterium"]["energy"]["consumption factor"]["move"].toDouble())
,twitchingbact_consumption_factor_tentacle(mConfig["twitching bacterium"]["energy"]["consumption factor"]["tentacle"].toDouble())
,twitchingbact_consumption_factor_fatigue(mConfig["twitching bacterium"]["energy"]["consumption factor"]["fatigue"].toDouble())

,poisonbact_min_energy(mConfig["poison bacterium"]["energy"]["min"].toDouble())
,poisonbact_max_energy(mConfig["poison bacterium"]["energy"]["max"].toDouble())
,poisonbact_min_radius(mConfig["poison bacterium"]["radius"]["min"].toDouble())
,poisonbact_max_radius(mConfig["poison bacterium"]["radius"]["max"].toDouble())
,poisonbact_tumble_algo(mConfig["poison bacterium"]["tumble"]["algo"].toString())
,poisonbact_poison_delay(sf::seconds(mConfig["poison bacterium"]["poison delay"].toDouble()))

,obstacle_radius(mConfig["obstacle"]["radius"].toDouble())
,obstacle_gradient_factor(mConfig["obstacle"]["gradient factor"].toDouble())
,obstacle_texture(mConfig["obstacle"]["texture"].toString())
{}

// TODO : getter for debug
void Config::switchDebug(){
    mConfig["debug"] = j::boolean(!mConfig["debug"].toBool());
    simulation_debug = mConfig["debug"].toBool();
}

bool Config::getDebug(){
return simulation_debug;
}
