#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "A3.h"

#define ALPHA 15.0 // the constant alpha, which is the normalization constant

// 检查是否为加强词
int isIntensifier(const char *word)
{
    const char *intensifiers[] = {
        "very", "extremely", "incredibly", "so", "totally", "completely", "remarkably", "really", "particularly"};
    int numIntensifiers = sizeof(intensifiers) / sizeof(intensifiers[0]);
    for (int i = 0; i < numIntensifiers; i++)
    {
        if (strcasecmp(word, intensifiers[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// 检查是否为否定词
int isNegation(const char *word)
{
    const char *negations[] = {
        "not", "never", "no", "none", "nobody", "nowhere", "neither", "cannot", "can't", "won't", "isn't", "doesn't"};
    int numNegations = sizeof(negations) / sizeof(negations[0]);
    for (int i = 0; i < numNegations; i++)
    {
        if (strcasecmp(word, negations[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// 检查是否为全大写单词
int isAllCaps(const char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]) && !isupper(word[i]))
        {
            return 0;
        }
    }
    return 1;
}

// 计算情绪复合得分
float calculateCompoundScore(const char *sentence, WordData *lexicon, int wordCount)
{
    float totalScore = 0.0;
    int validWordCount = 0;
    char *token = strtok(strdup(sentence), " ");
    int applyBoost = 0;
    int isNegated = 0;

    while (token != NULL)
    {
        // 检查是否为否定词
        if (isNegation(token))
        {
            isNegated = 1;
        }
        else if (isIntensifier(token))
        {
            applyBoost = 1;
        }
        else
        {
            for (int i = 0; i < wordCount; i++)
            {
                if (strcasecmp(token, lexicon[i].word) == 0)
                {
                    float score = lexicon[i].value1;

                    // 处理全大写的加强效果
                    if (isAllCaps(token))
                    {
                        score *= 1.5;
                    }

                    // 应用加强效果
                    if (applyBoost)
                    {
                        score += score * 0.293; // 增强系数
                        applyBoost = 0;         // 重置标记
                    }

                    // 应用否定效果
                    if (isNegated)
                    {
                        score *= -0.5;
                        isNegated = 0; // 重置标记
                    }

                    totalScore += score;
                    validWordCount++;
                    break;
                }
            }
        }
        token = strtok(NULL, " ");
    }

    free(token);

    // 归一化情绪得分
    float compoundScore = (validWordCount > 0) ? totalScore / sqrt(totalScore * totalScore + ALPHA) : 0.0;
    return compoundScore;
}
