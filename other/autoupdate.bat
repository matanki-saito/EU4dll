cd /d %~dp0

SET pluginMD5=
SET exeMD5=

rem https://stackoverflow.com/questions/38771114/saving-result-of-certutil-hashfile-to-a-variable-and-remove-spaces-of-the-hash

setlocal enabledelayedexpansion
set /a count=1 
for /f "skip=1 delims=:" %%a in ('CertUtil -hashfile ./plugin.dll MD5') do (
  if !count! equ 1 set "pluginMD5=%%a"
  set/a count+=1
)

set /a count=1 
for /f "skip=1 delims=:" %%a in ('CertUtil -hashfile ../eu4.exe MD5') do (
  if !count! equ 1 set "exeMD5=%%a"
  set/a count+=1
)

set url=https://d3mq2c18xv0s3o.cloudfront.net/api/v1/distribution/144728261/%exeMD5%?dll_md5=%pluginMD5%

call "curl.exe" -k -f --connect-timeout 3 -m 6 -s -o "Plugin.dll" %url%
