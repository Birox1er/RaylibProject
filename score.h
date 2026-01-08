#ifndef SCORE_H /* L'écriture ici présente n'est pas universelle */
#define SCORE_H
#include <Raylib.h>
#include <stdlib.h>
#define SCORE_DATA_FILE   "score.data"
// pour cette partie je me suis servi de l'exemple core_storage_value de raylib
bool SaveNewScore(int score)
{
    bool success = false;
    int highScoreTab=10;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    int position=0;;
    unsigned char *fileData = LoadFileData(SCORE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL)
    {
        if (dataSize <= (highScoreTab*sizeof(int)))
        {
        newDataSize = (highScoreTab + 1)*sizeof(int);
        newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);
            
            if (newFileData != NULL)
            {
                int *dataPtr = (int *)newFileData;
                for(int i=0;i<highScoreTab;++i)
                {
                    if(dataPtr[i]>score)
                    {
                        for(int j=highScoreTab-1;j>i;j--)
                        {
                            dataPtr[j] = dataPtr[j-1] ;
                        }
                        dataPtr[i] = score;
                        break;
                    }
                    
                }
 
            }
            else
            {
                // RL_REALLOC failed
                TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", SCORE_DATA_FILE, dataSize, highScoreTab*sizeof(int));

                // We store the old size of the file
                newFileData = fileData;
                newDataSize = dataSize;
            }
        }
        else
        {
                // Store the old size of the file
            newFileData = fileData;
            newDataSize = dataSize;

                // Replace value on selected position
                
            int *dataPtr = (int *)newFileData;
            for(int i=0;i<highScoreTab;++i)
            {
                if(dataPtr[i]>score)
                {
                    for(int j=highScoreTab-1;j>i;j--)
                        {
                            dataPtr[j] = dataPtr[j-1] ;
                        }
                    dataPtr[i] = score;
                    break;
                }
            }
        }
        success = SaveFileData(SCORE_DATA_FILE, newFileData, dataSize);
        RL_FREE(newFileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", SCORE_DATA_FILE,   score);   
    }
    else
    {
        dataSize = (highScoreTab)*sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[0] = score;
        for(int i=1;i<highScoreTab;++i)
        {
            TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", SCORE_DATA_FILE);
            dataPtr[i] = 999;
        }
        success = SaveFileData(SCORE_DATA_FILE, fileData, dataSize);
        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", SCORE_DATA_FILE, score);
        
    }

    return success;
}
int LoadStorageScore(unsigned int position)
{
    int value = 999;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(SCORE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < ((int)(position*4))) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", SCORE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", SCORE_DATA_FILE, value);
    }

    return value;
}


#endif