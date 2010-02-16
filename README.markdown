**THIS IS VERY-VERY EXPERIMENTAL AND HACKISH. USE ON YOUR OWN RISK.**

Thread Backtrace
================

It adds Thread#backtrace. Although I abuse private APIs of Ruby, no ruby patches are required. It **does not** work with 1.9.

Installation is simple as

    gem install thread_backtrace

Example
-------

    >> require 'thread_backtrace'
    => true
    >> def a; b; end; def b; c; end; def c; sleep 10; end
    => nil
    >> Thread.fork { a }.backtrace
    => ["(irb):2:in `c'", "(irb):2:in `b'", "(irb):2:in `a'", "(irb):3:in `irb_binding'", "(irb):3:in `fork'", "(irb):3:in `irb_binding'", "/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/irb/workspace.rb:52:in `irb_binding'", "/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/irb/workspace.rb:52"]

Also it adds caller_for_all_threads method to kernel. But it's not the same as output of REE (it doesn't skip the first entry for the current thread).
