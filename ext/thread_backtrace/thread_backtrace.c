#include <ruby.h>
#include <node.h>
#include <env.h>

extern rb_thread_t rb_main_thread, rb_curr_thread;
extern struct FRAME * ruby_frame;

static rb_thread_t find_thread(VALUE thread)
{
  rb_thread_t t = rb_main_thread;
  do {
    if (t->thread == thread) return t;

    t = t->next;
  } while (t != rb_main_thread);

  // todo: raise exception
  return 0;
}

static void * convert_pointer(rb_thread_t thread, void * ptr)
{
  VALUE *p = (VALUE*)ptr;

  if(thread == rb_curr_thread) return ptr;

  if(p >= thread->stk_pos && p <= thread->stk_pos + thread->stk_len)
    return (p - thread->stk_pos) + thread->stk_ptr;

  return p;
}

static VALUE thread_backtrace(VALUE self)
{
  rb_thread_t t = find_thread(self);
  struct FRAME *frame, *prev_frame;
  char buf[BUFSIZ];
  VALUE ary;
  NODE *n;

  if (t == rb_curr_thread) {
    frame = ruby_frame;
  } else {
    frame = convert_pointer(t, t->frame);
  }

  ary = rb_ary_new();
  if (frame->last_func == ID_ALLOCATOR) {
    frame = convert_pointer(t, frame->prev);
  }

  for (; frame && (n = frame->node); frame = prev_frame) {
    prev_frame = convert_pointer(t, frame->prev);

    if (prev_frame && prev_frame->last_func) {
      if (prev_frame->node == n) {
        if (prev_frame->last_func == frame->last_func) continue;
      }
      snprintf(buf, BUFSIZ, "%s:%d:in `%s'", n->nd_file, nd_line(n), rb_id2name(prev_frame->last_func));
    } else {
      snprintf(buf, BUFSIZ, "%s:%d", n->nd_file, nd_line(n));
    }
    rb_ary_push(ary, rb_str_new2(buf));
  }

  return ary;
}

void Init_thread_backtrace()
{
  VALUE cThread = rb_define_class("Thread", rb_cObject);
  rb_define_method(cThread, "backtrace", thread_backtrace, 0);
}