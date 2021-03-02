/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <string>


namespace common::lsrc
{
class Stream
{
public:
    explicit Stream() = default;
    virtual ~Stream() = default;

    virtual void put(std::string&& msg) = 0;
};
}  // namespace common::lsrc
