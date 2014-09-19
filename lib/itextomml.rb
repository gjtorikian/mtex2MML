require 'itex2MML'
require 'thread'

module Itex2MML
  class Error < RuntimeError; end

  class Parser
    def self.semaphore
      @semaphore ||= Mutex.new
    end

    def html_filter(string)
      parse(string, :itex2MML_html_filter)
    end

    def filter(string)
      parse(string, :itex2MML_filter)
    end

    def inline_filter(string)
      parse("\$#{string}\$", :itex2MML_filter)
    end

    def block_filter(string)
      parse("\$\$#{string}\$\$", :itex2MML_filter)
    end

  private

    def parse(string, message)
      str = as_bytes(string.to_str)
      self.class.semaphore.synchronize do
        raise Itex2MML::Error unless Itex2MML.send(message, str, str.length) == 0
        as_utf8(Itex2MML.itex2MML_output)
      end
    end

    if "".respond_to?(:force_encoding)
      def as_bytes(string)
        string.force_encoding("ASCII-8BIT")
      end
      def as_utf8(string)
        string.force_encoding("UTF-8")
      end
    else
      def as_bytes(string)
        string
      end
      def as_utf8(string)
        string
      end
    end

  end
end