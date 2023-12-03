
#pragma once

#include "Config.hpp"

namespace clg_cursescpp {

  class IWindow
  {
    public:
      virtual ~IWindow() {}
      virtual pWIN getWindow() const = 0;
  };

}