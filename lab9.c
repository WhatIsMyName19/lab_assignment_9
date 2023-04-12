#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* record;
	struct HashType* next;
	int flag;
};

// Compute the hash function
int hash(int x)
{
	int hashedInt = x % 1000;
	
	hashedInt /= 2;
	
	return hashedInt;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		struct HashType* temp = &pHashArray[i];

		while (temp != NULL && temp->flag == 1)
		{
			printf("index %d -> %d, %c, %d\n", i, temp->record->id, temp->record->name, temp->record->order);
			
			temp = temp->next;
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	int hashLength = 500;
	struct HashType* hashedArr = malloc(hashLength * sizeof(struct HashType));

	for (int i = 0; i < recordSz; i++)
	{
		int hashedNum = hash(pRecords[i].id);
		
		struct HashType* temp = &hashedArr[hashedNum];

		while (temp->flag == 1)
			temp = temp->next;

		temp->record = &pRecords[i];
		temp->flag = 1;

		temp->next = NULL;
		temp++;
	}

	displayRecordsInHash(hashedArr, hashLength);

	free(pRecords);
	free(hashedArr);
	return 0;
}
