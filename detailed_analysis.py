import re
from collections import defaultdict

# Read the log file
with open('log_data.txt', 'r') as f:
    content = f.read()

tokens = content.split()

print("=== DETAILED PATTERN ANALYSIS ===\n")

# 1. Analyze the clean initial sequence
print("1. CLEAN INITIAL SEQUENCE:")
print("-" * 40)
clean_tokens = []
corruption_start = -1
for i, token in enumerate(tokens):
    if 'MM' in token or (len(token) > 3 and token.count('M') > 1):
        corruption_start = i
        break
    clean_tokens.append(token)

print(f"Clean tokens before corruption: {len(clean_tokens)}")
print(f"Corruption starts at token index: {corruption_start}")
print("\nClean sequence:")
print(" ".join(clean_tokens))

# 2. Analyze M-number progression
print("\n\n2. M-NUMBER PROGRESSION ANALYSIS:")
print("-" * 40)
m_numbers_in_order = []
for token in clean_tokens:
    match = re.match(r'^M(\d+)$', token)
    if match:
        m_numbers_in_order.append(int(match.group(1)))

print(f"M-numbers in order: {m_numbers_in_order}")
if m_numbers_in_order:
    print(f"Range: M{min(m_numbers_in_order)} to M{max(m_numbers_in_order)}")
    print(f"Sequential progression: {m_numbers_in_order == list(range(min(m_numbers_in_order), max(m_numbers_in_order) + 1))}")

# 3. Analyze corruption patterns
print("\n\n3. CORRUPTION PATTERN ANALYSIS:")
print("-" * 40)
corruption_types = defaultdict(list)
for token in tokens[corruption_start:]:
    if 'M' in token:
        # Count number of M's
        m_count = token.count('M')
        # Extract all M-numbers
        m_numbers = re.findall(r'M+(\d+)', token)
        
        if m_count == 1 and len(m_numbers) == 1:
            corruption_types['Clean'].append(token)
        elif token.startswith('MM') and len(m_numbers) == 1:
            corruption_types['Double-M prefix'].append(token)
        elif len(m_numbers) > 1:
            corruption_types['Multiple M-numbers concatenated'].append(token)
        else:
            corruption_types['Other corruption'].append(token)

for corruption_type, examples in corruption_types.items():
    print(f"\n{corruption_type}:")
    print(f"  Count: {len(examples)}")
    print(f"  First 5 examples: {examples[:5]}")

# 4. Analyze M39 repetition pattern
print("\n\n4. M39 REPETITION PATTERN:")
print("-" * 40)
m39_section = []
for i in range(len(tokens)-1, -1, -1):
    if 'M39' in tokens[i]:
        m39_section.insert(0, tokens[i])
    else:
        if m39_section:  # We've found the end of M39 section
            break

print(f"M39 section length: {len(m39_section)} tokens")
print(f"Unique M39 patterns: {set(m39_section)}")
print(f"Pattern: {m39_section[:10]}... (first 10)")

# 5. State machine analysis
print("\n\n5. STATE MACHINE BEHAVIOR:")
print("-" * 40)
print("Initial state: M_NRDY -> ISR_RUN (repeated 8 times)")
print("Transition: RdyOut signals ready state")
print("Main sequence: M0 -> VPN_CHG -> M1 through M12")
print("SOF events: SOF_LO at M11, SOF_HI at M12")
print("Corruption begins: After M12, data becomes concatenated")
print("Terminal state: System appears stuck at M39 (repeating)")

# 6. Look for specific patterns in corrupted data
print("\n\n6. PATTERN EXTRACTION FROM CORRUPTED DATA:")
print("-" * 40)
# Try to extract the intended sequence
extracted_sequence = []
for token in tokens[corruption_start:]:
    # Extract all M-numbers from concatenated strings
    numbers = re.findall(r'M+(\d+)', token)
    extracted_sequence.extend([f'M{n}' for n in numbers])

# Count unique M-numbers in corrupted section
unique_in_corrupted = set(extracted_sequence)
print(f"Unique M-numbers found in corrupted section: {sorted(unique_in_corrupted)}")
print(f"Total M-numbers extracted from corrupted data: {len(extracted_sequence)}")

# Check if we can reconstruct a pattern
print("\nPossible intended sequence from corrupted data:")
reconstructed = []
for num in extracted_sequence[:30]:  # First 30
    if num not in reconstructed or num == reconstructed[-1]:
        reconstructed.append(num)
print(" -> ".join(reconstructed))