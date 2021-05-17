import urllib3

http = urllib3.PoolManager()

response = http.request('PUT', 'http://localhost:12345')

print(response.data) # Raw data.
print(response.data.decode('utf-8')) # Text.
print(response.status) # Status code.
print(response.headers['Content-Type']) # Content type.
