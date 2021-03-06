#ifndef RBX_BUILTIN_LOGGER_HPP
#define RBX_BUILTIN_LOGGER_HPP

#include "builtin/object.hpp"

namespace rubinius {
  class String;

  class Logger : public Object {
  public:
    const static object_type type = LoggerType;

  private:
    String* name_;    // slot
    String* format_;  // slot

  public:
    /* accessors */

    attr_accessor(name, String);
    attr_accessor(format, String);

  public:
    static void init(STATE);
    static Logger* create(STATE);

    // Rubinius.primitive+ :logger_allocate
    static Logger* allocate(STATE, Object* self);

    // Rubinius.primitive :logger_write
    Object* write(STATE, String* message);

    // Rubinius.primitive :logger_fatal
    Object* fatal(STATE, String* message);

    // Rubinius.primitive :logger_error
    Object* error(STATE, String* message);

    // Rubinius.primitive :logger_warn
    Object* warn(STATE, String* message);

    // Rubinius.primitive :logger_info
    Object* info(STATE, String* message);

    // Rubinius.primitive :logger_debug
    Object* debug(STATE, String* message);

    class Info : public TypeInfo {
    public:
      BASIC_TYPEINFO(TypeInfo)
    };
  };
}

#endif
