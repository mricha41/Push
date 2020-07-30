#ifndef PHYSICSHELPERS_HPP
#define PHYSICSHELPERS_HPP

namespace pk
{
    namespace physics
    {
        //number of tiles per character in the scene
        //I chose 16 pixel tiles, but this could be
        // any value as long as it's consistent
        //see: http://box2d.org/manual.pdf
        const float tilex = 16.f;
        const float tiley = 16.f;

        const float PPM = tilex;
        const float MPP = 1.f/PPM;

        namespace
        {
            ///////////////////////////////////
            /// \fn glm::vec2 metersToPixels(b2Vec2 meters)
            /// \brief Convert meters to pixel units.
            /// \param b2Vec2 meters - value in meters specified as floats.
            ///////////////////////////////////
            glm::vec2 metersToPixels(b2Vec2 meters)
            {
                return { meters.x*PPM, meters.y*PPM };
            };

            ////////////////////////////////////
            /// \fn b2Vec2 pixelsToMeters(glm::vec2 pixels)
            /// \brief Convert pixel units to meters.
            /// \param glm::vec2 pixels - value in pixels specified as floats.
            ////////////////////////////////////
            b2Vec2 pixelsToMeters(glm::vec2 pixels)
            {
                return { pixels.x/PPM, pixels.y/PPM };
            };
        }
    }
}
#endif // PHYSICSHELPERS_HPP
