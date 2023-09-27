Import("env")

env.Replace(PROGNAME="firmware_%s" % env["PIOENV"])