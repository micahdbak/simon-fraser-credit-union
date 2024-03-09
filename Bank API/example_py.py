import dns_bank_api as dns

def main():
	result = dns.bank_transfer("13513780037206503511", "15406478860434420512", "3156077800","-100.1")
	result2 = dns.bank_get_info("13513780037206503511")
	result3 = dns.bank_get_info("15406478860434420512")
	print(result)
	print(result2)
	print(result3)
main()
