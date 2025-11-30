from libbs import create_entries

def main():
    url_input = 'sample.com'
    n_entries = 3
    n_flips = 1

    try:
        entries = create_entries(url_input, n_entries, n_flips)
        print("Generated entries:")
        for entry in entries:
            print(entry)
    except ValueError as e:
        print(e)

if __name__ == "__main__":
    main()
