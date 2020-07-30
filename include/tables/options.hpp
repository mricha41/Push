#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <cereal/archives/json.hpp>

namespace pk
{

namespace options
{

/////////////////////////////
/// \struct optionsCereal
/// \brief The data structure
/// holding all of the options settings.
/////////////////////////////
struct optionsCereal
{
    int d_musicVolume;
    int d_soundEffectVolume;
    bool d_fullscreen;
    int d_resolutionX;
    int d_resolutionY;
};

///////////////////////////////
/// \fn template<class Archive> void save(Archive & archive, optionsCereal const & ops)
/// \brief Save operation for the
/// options data. Serialized to json.
///////////////////////////////
template<class Archive>
void save(Archive & archive, optionsCereal const & ops)
{
  archive( cereal::make_nvp("Music Volume", ops.d_musicVolume), cereal::make_nvp("Sound Effect Volume", ops.d_soundEffectVolume),
          cereal::make_nvp("Fullscreen", ops.d_fullscreen), cereal::make_nvp("Resolution X", ops.d_resolutionX),
          cereal::make_nvp("Resolution Y", ops.d_resolutionY));
}

///////////////////////////////
/// \fn template<class Archive> void load(Archive & archive, optionsCereal & ops)
/// \brief Load operation for the
/// json serialized options data.
///////////////////////////////
template<class Archive>
void load(Archive & archive, optionsCereal & ops)
{
  archive( cereal::make_nvp("Music Volume", ops.d_musicVolume), cereal::make_nvp("Sound Effect Volume", ops.d_soundEffectVolume),
          cereal::make_nvp("Fullscreen", ops.d_fullscreen), cereal::make_nvp("Resolution X", ops.d_resolutionX),
          cereal::make_nvp("Resolution Y", ops.d_resolutionY));
}

}

}

#endif // OPTIONS_HPP
