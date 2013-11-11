def unpack_data():
    curr_version = open('version').read()
    try:
        if open('version_ready').read() == curr_version:
            return
    except IOError:
        pass

    import tarfile
    print 'extracting data...'
    tarfile.open('data.tgz').extractall()

    with open('version_ready', 'w') as f:
        f.write(curr_version)
