// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "FunctionHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"
#include "function/CFunction.h"
#include "function/CExpression.h"

/**
 * Replace Function with the name type of the handler and implement the
 * three methods below.
 */
FunctionHandler::FunctionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Function)
{
  init();
}

// virtual
FunctionHandler::~FunctionHandler()
{}

// virtual
CXMLHandler * FunctionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  const char * type;
  CEvaluationTree::Type Type;
  const char * Name;
  const char * Reversible;
  size_t Index;

  CEvaluationTree* pEvaluationTree = NULL;

  switch (mCurrentElement.first)
    {
      case Function:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        type = mpParser->getAttributeValue("type", papszAttrs);
        Type = toEnum(type, CEvaluationTree::XMLType, CEvaluationTree::UserDefined);

        Reversible = mpParser->getAttributeValue("reversible", papszAttrs, false);

        if (!Reversible) // We may have an old file format using positive
          Reversible = mpParser->getAttributeValue("positive", papszAttrs, "unspecified");

        mpData->mPredefinedFunction = false;
        mpData->mFunctionParameterKeyMap.clear();
        mExistingFunctionIndex.clear();

        pEvaluationTree = CEvaluationTree::create(Type);

        if (Type == CEvaluationTree::Expression)
          {
            mpData->pFunction = NULL;

            mpData->mpExpression = static_cast< CExpression * >(pEvaluationTree);
            mpData->mKey2ObjectiveFunction[mKey] = mpData->mpExpression;
          }
        else
          {
            mpData->mpExpression = NULL;

            mpData->pFunction = static_cast<CFunction *>(pEvaluationTree);
            mpData->pFunction->setObjectName(Name);

            if (!strcmp(Reversible, "true"))
              mpData->pFunction->setReversible(TriTrue);
            else if (!strcmp(Reversible, "false"))
              mpData->pFunction->setReversible(TriFalse);
            else
              mpData->pFunction->setReversible(TriUnspecified);

            Index = mpData->pFunctionList->getIndex(Name);

            if (Index != C_INVALID_INDEX) // A function with that name exists.
              {
                mExistingFunctionIndex.insert(Index);

                switch ((*mpData->pFunctionList)[Index].getType())
                  {
                    case CEvaluationTree::MassAction:

                      if (Type == CEvaluationTree::MassAction)
                        {
                          pdelete(mpData->pFunction);
                          mpData->pFunction = &mpData->pFunctionList->operator[](Index);
                          mpData->mPredefinedFunction = true;
                        }
                      else
                        {
                          size_t Counter = 0;
                          std::string NewName;

                          while (true)
                            {
                              Counter++;
                              std::ostringstream ss;
                              ss << Name << " [" << Counter << "]";
                              NewName = ss.str();
                              Index = mpData->pFunctionList->getIndex(NewName);

                              if (Index == C_INVALID_INDEX)
                                break;

                              mExistingFunctionIndex.insert(Index);
                            }

                          mpData->pFunction->setObjectName(NewName);
                        }

                      break;

                    case CEvaluationTree::PreDefined:

                      if (Type == CEvaluationTree::PreDefined)
                        {
                          pdelete(mpData->pFunction);
                          mpData->pFunction = &mpData->pFunctionList->operator[](Index);
                          mpData->mPredefinedFunction = true;
                        }
                      else
                        {
                          size_t Counter = 0;
                          std::string NewName;

                          while (true)
                            {
                              Counter++;
                              std::ostringstream ss;
                              ss << Name << " [" << Counter << "]";
                              NewName = ss.str();
                              Index = mpData->pFunctionList->getIndex(NewName);

                              if (Index == C_INVALID_INDEX)
                                break;

                              mExistingFunctionIndex.insert(Index);
                            }

                          mpData->pFunction->setObjectName(NewName);
                        }

                      break;

                    case CEvaluationTree::UserDefined:
                    case CEvaluationTree::Function:
                      // Create a unique name
                    {
                      size_t Counter = 0;
                      std::string NewName;

                      while (true)
                        {
                          Counter++;
                          std::ostringstream ss;
                          ss << Name << " [" << Counter << "]";
                          NewName = ss.str();
                          Index = mpData->pFunctionList->getIndex(NewName);

                          if (Index == C_INVALID_INDEX)
                            break;

                          mExistingFunctionIndex.insert(Index);
                        }

                      mpData->pFunction->setObjectName(NewName);
                    }

                    break;

                    default:
                      break;
                  }
              }
          }

        break;

      case MiriamAnnotation:
      case Comment:
      case ListOfUnsupportedAnnotations:
      case ListOfParameterDescriptions:
      case Expression:
      case MathML:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool FunctionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Function:
        finished = true;
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * FunctionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Function, HANDLER_COUNT}},
    {"Function", Function, Function, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, Expression, MathML, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, Expression, MathML, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, Expression, MathML, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {Expression, MathML, HANDLER_COUNT}},
    {"Expression", Expression, CharacterData, {ListOfParameterDescriptions, AFTER, HANDLER_COUNT}},
    {"MathML", MathML, MathML, {ListOfParameterDescriptions, AFTER, HANDLER_COUNT}},
    {"ListOfParameterDescriptions", ListOfParameterDescriptions, ListOfParameterDescriptions, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}