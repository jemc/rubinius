# depends on: class.rb

##
# DelegatedMethod is used to implement Module#define_method

module Rubinius
  class DelegatedMethod < Executable
    def initialize(method, receiver, pass_self=false)
      @method = method
      @receiver = receiver
      @pass_self = pass_self
    end

    def call(called_object, called_method, *args, &block)
      args.unshift called_object if @pass_self
      @receiver.__send__(@method, *args, &block)
    end

    # @todo: figure this out
    alias_method :activate, :call

    def arity
      if @method.respond_to? :arity
        @method.arity
      else
        0 # meh
      end
    end
  end
end
