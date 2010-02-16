require 'rubygems'  unless defined?(Gem)
require 'rake'      unless defined?(Rake)
require 'rake/gempackagetask'

spec = Gem::Specification.new do |s|
  s.name = 'thread_backtrace'
  s.version = '0.1.1'
  s.platform = Gem::Platform::RUBY
  s.has_rdoc = true
  s.authors = ['Eugene Pimenov']
  s.extra_rdoc_files = ["README.markdown"]
  s.summary = "Adds Thread\#backtrace"
  s.description = "Adds Thread\#backtrace for inspecting backtrace of a thread. Only supports 1.8"
  s.files = %w(README.markdown Rakefile) + Dir.glob("{ext,lib}/**/*.{rb,c}")
  s.extensions << 'ext/thread_backtrace/extconf.rb'
  s.require_paths = ["lib"]
  s.required_ruby_version = "~>1.8"
end

Rake::GemPackageTask.new(spec) do |pkg|
  pkg.gem_spec = spec
end
