import os
import datetime
import httplib
import sys
import traceback

try:
    import json
except ImportError:
    import microjson as json

DEFAULT_DSN = None

class RavenError(Exception):
    pass

def _parse_dsn(dsn):
    proto, rest = dsn.split('://', 1)
    login, rest = rest.split('@', 1)
    host, path = rest.split('/', 1)
    return proto, host, path, login

def _make_event_id():
    return os.urandom(16).encode('hex') # uuid4

def _report_raw(event, dsn=None):
    data = json.dumps(event)
    dsn = dsn or DEFAULT_DSN
    proto, host, path, login = _parse_dsn(dsn)
    key, secret = login.split(':', 1)
    conntype = {'http': httplib.HTTPConnection,
                'https': httplib.HTTPSConnection}[proto]
    conn = conntype(host)
    conn.request('POST', '/api/' + path + '/store/',
                 body=data, headers={
                     'X-Sentry-Auth': 'Sentry sentry_version=4,'
                     + ('sentry_key=%s,sentry_secret=%s' % (key, secret)),
                     'User-Agent': 'RavenSimplePython/0',
                     'Host': host,
                 })
    resp = conn.getresponse()
    code = resp.status
    if code != 200:
        raise RavenError('Failure %s - %r' % (code, resp.reason))

def report(message, level='error', dsn=None, **kwargs):
    event = dict(kwargs,
                 event_id=_make_event_id(),
                 timestamp=datetime.datetime.utcnow().isoformat(),
                 platform='python',
                 logger='root',
                 level=level,
                 message=message)
    _report_raw(event, dsn=dsn)

def _format_exc(tb):
    frames = []
    while tb:
        frame = tb.tb_frame
        frames.append(dict(
            lineno=tb.tb_lineno,
            filename=tb.tb_frame.f_code.co_filename,
            function=tb.tb_frame.f_code.co_name,
            vars=dict( (k, repr(v)) for k, v in tb.tb_frame.f_locals.items() )
        ))
        tb = tb.tb_next

    return frames

def _dont_crash(func):
    def dont_crash_wrap(*args, **kwargs):
        try:
            func(*args, **kwargs)
        except Exception:
            traceback.print_exc()

    return dont_crash_wrap

@_dont_crash
def report_exception(exc=None, traceback=None, **kwargs):
    if not traceback:
        traceback = sys.exc_info()[2]
    if not exc:
        exc = sys.exc_info()[1]
    report(message=type(exc).__name__ + ': ' + str(exc),
           exception=[{
               'type': type(exc).__name__,
               'value': str(exc),
               'stacktrace': dict(frames=_format_exc(traceback))
           }],
           **kwargs)

if __name__ == '__main__':
    dsn = 'http://27a9cc90b4b448cc86d79ad5ecb5462a:f2eb6025eedf416bab5fe63da3617687'\
          '@sentrypublic.civsync.com/3'
    try:
        foobar
    except Exception:
        report_exception(dsn=dsn)
