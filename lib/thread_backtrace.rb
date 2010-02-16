require 'thread_backtrace/thread_backtrace'

module Kernel
  def caller_for_all_threads
    c, Thread.critical = Thread.critical, true

    Thread.list.inject({}) { |h, t| h.update t => t.backtrace }
  ensure
    Thread.critical = c
  end
end