#ifndef SENSORDATA_HPP
#define SENSORDATA_HPP

namespace pk
{

/////////////////////////////
/// \enum SensorType
/// \brief The type of sensor
/// data represented.
/////////////////////////////
enum SensorType
{
    FOOT,
    LEFT,
    RIGHT,
    TOP
};

/////////////////////////////////
/// \class SensorData
/// \brief A class wrapping some
/// user data for Box2D fixtures.
/// Includes data for number of contacts
/// being made to the sensor and an ID
/// useful for identifying fixtures
/// when a contact triggers a Box2D
/// contact listener event.
/////////////////////////////////
class SensorData
{
    public:
        ////////////////////////////
        /// \fn SensorData()
        /// \brief Default constructor.
        ////////////////////////////
        SensorData();

        ////////////////////////////
        /// \fn SensorData(int id)
        /// \brief Preferred constructor.
        ////////////////////////////
        SensorData(int id)
        {
            m_id = id;
            m_contacts = 0;
        };

        ~SensorData()
        {

        }

        ///////////////////////////
        /// \fn contactMade()
        /// \brief Increments the number
        /// of contacts made to the sensor.
        /// Call this function inside a
        /// Box2D contact listener function when
        /// filtering contacts.
        ///////////////////////////
        void contactMade()
        {
            m_contacts++;
            //if(m_id == SensorType::LEFT || m_id == SensorType::RIGHT || m_id == SensorType::TOP)
            //    printf("contacts made: %i\n", m_contacts);
        };

        ///////////////////////////
        /// \fn contactEnded()
        /// \brief Decrements the number
        /// of contacts made to the sensor.
        /// Call this function inside a
        /// Box2D contact listener function when
        /// filtering contacts.
        ///////////////////////////
        void contactEnded()
        {
            m_contacts--;
            //if(m_id == SensorType::LEFT || m_id == SensorType::RIGHT || m_id == SensorType::TOP)
            //    printf("contacts made: %i\n", m_contacts);
        };

        ////////////////////////////
        /// \fn getContacts()
        /// \brief Get the number of contacts
        /// currently being made to the sensor.
        /// \return int - the number of
        /// contacts given as an int.
        ////////////////////////////
        int getContacts(){ return m_contacts; };
        int getID(){ return m_id; };

    private:
        int m_id; ///< the sensor's ID.
        int m_contacts; ///< the number of contacts made with the sensor.
};

}

#endif //SENSORDATA_HPP
