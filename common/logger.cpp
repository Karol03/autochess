/**
 * Created by Karol Dudzic @ 2021
 */
#include "logger.hpp"


namespace common
{
std::unique_ptr<lsrc::Stream> Logger::m_stream = nullptr;
std::mutex Logger::m_mutex = {};
}  // namespace common
