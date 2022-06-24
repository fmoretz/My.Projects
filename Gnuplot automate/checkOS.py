import platform
checkOS = platform.system()
release = platform.release()
version = platform.version()

print(f'OS_____: {checkOS}')
print(f'Release: {release}')
print(f'Version: {version}')