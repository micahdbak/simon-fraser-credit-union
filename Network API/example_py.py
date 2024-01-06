import dns_network_api as dns

def main():
	result = dns.network_check("888")
	print(result)
main()