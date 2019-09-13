// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.


static const char* shinyServerString =  "## server file\n"
"server <- function(input, output, session) {\n"
"  ## limit for the input file size\n"
"  options(shiny.maxRequestSize=30*1024^2) \n"
"  ## to store the current selection\n"
"  selection <- renderText({\n"
"    return(unlist(get_selected(input$taskSelection)))\n"
"  })\n"
"  \n"
"  ## to store the error encountered\n"
"  error <- renderText({\n"
"    if (is.null(inputFile$dataPaths))\n"
"      error <- c('No model file loaded !!')\n"
"    else if (is.null(inputFile$modelData))\n"
"      error <- c('Please load a valid model file!!')\n"
"    else if (exists('message', where=resTask()))\n"
"      error <- c(resTask()$message)\n"
"    else\n"
"      error <- ''\n"
"    \n"
"    return(error)\n"
"  })\n"
"  \n"
"  ## to display the error \n"
"  output$errorOut <- renderText({\n"
"    textOutput('error')\n"
"    return(error())\n"
"  })\n"
"  \n"
"  ## To store the information of input model\n"
"  inputFile <- reactiveValues()\n"
"  observe({\n"
"    \n"
"    inputFile$fileNames <- dir('copasi')\n"
"    inputFile$dataPaths <- paste0('copasi/',inputFile$fileNames)\n"
"    \n"
"    inputFile$dirName <- dirname(inputFile$dataPaths)\n"
"    inputFile$modelData <- NULL\n"
"    inputFile$rootnode <- NULL\n"
"    inputFile$modelLoaded <- FALSE\n"
"    for (i in 1:length(inputFile$fileNames)){\n"
"      inputFileName <- inputFile$fileNames[i]\n"
"      if (grepl('\\\\.cps$',inputFileName)){\n"
"        inputFile$modelData <- CoRC::loadModel(inputFile$dataPaths[i])\n"
"        inputFile$modelName <- inputFileName\n"
"        inputFile$rootnode <- xmlTreeParse(inputFile$dataPaths[i])\n"
"        inputFile$modelAttrs <- xmlAttrs(inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='Model']$Model)\n"
"        inputFile$modelLoaded <- TRUE\n"
"      }\n"
"    }\n"
"    \n"
"    if (is.null(inputFile$modelData)){\n"
"      return(error())\n"
"    }\n"
"\n"
"    inputFile$compartments <- CoRC::getCompartments(model=inputFile$modelData)\n"
"    inputFile$species <- CoRC::getSpecies(model=inputFile$modelData)\n"
"    inputFile$reactions <- CoRC::getReactions(model=inputFile$modelData)\n"
"    inputFile$globalQuantities <- CoRC::getGlobalQuantities(model=inputFile$modelData)\n"
"    inputFile$events <- CoRC::getEvents(model=inputFile$modelData)\n"
"    inputFile$parameters <- CoRC::getParameters(model=inputFile$modelData)\n"
"    inputFile$stoichiometry <- CoRC::getStoichiometryMatrix(model=inputFile$modelData)\n"
"    inputFile$linkMatrix <- CoRC::getLinkMatrix(model=inputFile$modelData)\n"
"    inputFile$settingsTC <- CoRC::getTC(model=inputFile$modelData)\n"
"    inputFile$settingsOpt <- CoRC::getOpt(model=inputFile$modelData)\n"
"    inputFile$settingsPE <- CoRC::getPE(model=inputFile$modelData)\n"
"    inputFile$taskList <- c('Compartments', 'Species', 'Reactions'\n"
"                            ,'Global Quantities', 'Events', 'Parameters'\n"
"                            ,'Stoichiometry','Steady State','Time Course'\n"
"                            ,'Metabolic Control Analysis','Optimization'\n"
"                            ,'Parameter Estimation', 'Linear Noise Approximation')\n"
"  })\n"
"  \n"
"  \n"
"  ## Theme functions for the plots\n"
"  theme_pm <- function () {\n"
"    theme_bw(base_size=12) + #base_family='Arial Black'\n"
"      theme(panel.grid=element_line(linetype='dashed', color='light grey', size=0.2),axis.ticks.length=unit(-0.15, 'cm'),axis.text.x = element_text(margin=unit(c(0.25,0.25,0.25,0.25),'cm')),axis.text.y = element_text(margin=unit(c(0.25,0.25,0.25,0.25),'cm')))\n"
"  }\n"
"  \n"
"  output$modelInfo <- renderText({\n"
"    if (is.null(inputFile$modelData))\n"
"      return()\n"
"    selectedTask = selection()\n"
"    strOut= paste('<h1>','Model Name:', inputFile$modelAttrs[[2]],'</h1>')\n"
"    if (selectedTask %in% inputFile$taskList ){\n"
"      if (selectedTask == 'Parameter Estimation' ){\n"
"        expfileName= ''\n"
"        valfileName= ''\n"
"        if (xmlSize(inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[6]][[2]][[9]]) >= 1){\n"
"          xmlList= xmlChildren(inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[6]][[2]][[9]][[1]])\n"
"          for (i in 1:xmlSize(xmlList)){\n"
"            paramValue= xmlToList(xmlList[[i]])\n"
"            if (paramValue[[1]] == 'File Name'){\n"
"              expfileName= paramValue[[3]]\n"
"              break\n"
"            }\n"
"          }\n"
"          if (expfileName %in% inputFile$fileNames){\n"
"            #file.copy(inputFile$dataPaths[inputFile$fileNames == expfileName], paste0(inputFile$dirName,'/',expfileName), overwrite = TRUE, recursive = FALSE,copy.mode = TRUE, copy.date = FALSE)\n"
"          }\n"
"          else\n"
"            expfileName= paste(' <font color=','red','>  Please load a valid data file along with the model. File name: <b>', expfileName ,'</b> </font> ')\n"
"        }\n"
"          \n"
"        if (xmlSize(inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[6]][[2]][[10]]) > 2){\n"
"          xmlList= xmlChildren(inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[6]][[2]][[10]][[1]])\n"
"          for (i in 1:xmlSize(xmlList)){\n"
"            paramValue= xmlToList(xmlList[[i]])\n"
"            if (paramValue[[1]] == 'File Name'){\n"
"              valfileName= paramValue[[3]]\n"
"              break\n"
"            }\n"
"          }\n"
"          if (valfileName %in% inputFile$fileNames){\n"
"            #file.copy(inputFile$dataPaths[inputFile$fileNames == valfileName], paste0(inputFile$dirName,'/',valfileName), overwrite = TRUE, recursive = FALSE,copy.mode = TRUE, copy.date = FALSE)\n"
"          }\n"
"          else\n"
"            valfileName= paste(' <font color=','red','>  Please load a valid data file along with the model. File name: <b>', valfileName ,'</b> </font> ')\n"
"        }\n"
"        strOut= paste(strOut, '<h2>',selectedTask,'</h2>')\n"
"        strOut= paste(strOut, '<pre><b> Experimental Data: </b>',expfileName,'<br> <br>')\n"
"        strOut= paste(strOut, '<b>Validation Data: </b>',valfileName,'<br>')\n"
"        strOut= paste(strOut, '<pre><b> Randomize Start Values: </b>',inputFile$settingsPE$randomize_start_values)\n"
"        strOut= paste(strOut, '<b>  Calculate Statistics: </b>',inputFile$settingsPE$calculate_statistics, '</pre></pre>')\n"
"      }\n"
"      else if (selectedTask == 'Optimization' ){\n"
"        strOut= paste(strOut, '<h2>',selectedTask,'</h2>')\n"
"        strOut= paste(strOut, '<pre><b> Expression: </b>',inputFile$settingsOpt$expression)\n"
"        strOut= paste(strOut, '<pre><b> Maxmize: </b>',inputFile$settingsOpt$maximize, '</pre>')\n"
"        strOut= paste(strOut, '<b>Subtask: </b>',inputFile$settingsOpt$subtask)\n"
"        strOut= paste(strOut, '<pre><b> Randomize Start Values: </b>',inputFile$settingsOpt$randomize_start_values)\n"
"        strOut= paste(strOut, '<b>  Calculate Statistics: </b>',inputFile$settingsOpt$calculate_statistics, '</pre></pre>')\n"
"      }\n"
"      else\n"
"        strOut= paste(strOut, '<h2>',selectedTask,'</h2>')\n"
"    }\n"
"    else if (selectedTask == 'Model' || inputFile$modelLoaded == T){\n"
"      strOut= paste('<pre><b> Model: </b>',inputFile$modelAttrs[[2]],'<br>')\n"
"      strOut= paste(strOut,'<pre><table><tr><th>Time Unit:</th><td>',inputFile$modelAttrs[[4]]\n"
"                    ,'</td><th>Volume Unit:</th><td>',inputFile$modelAttrs[[5]],'</td></tr>')\n"
"      strOut= paste(strOut,'<tr><th>Quantity Unit:</th><td>',inputFile$modelAttrs[[8]]\n"
"                    ,'</td><th>Area Unit:</th><td>',inputFile$modelAttrs[[6]],'</td></tr>')\n"
"      strOut= paste(strOut,'<tr><th>Avogadro Constant:</th><td>',inputFile$modelAttrs[[10]]\n"
"                    ,'</td><th>Length Unit:</th><td>',inputFile$modelAttrs[[7]],'</td></tr></table></pre></pre>')\n"
"      }\n"
"    return(strOut)\n"
"  })\n"
"  \n"
"  output$selectedMethod<- renderText({\n"
"    if (is.null(inputFile$rootnode))\n"
"      return()\n"
"    \n"
"    selectedTask = selection()\n"
"    if (selectedTask == 'Parameter Estimation' ){\n"
"      methodSetting= inputFile$settingsPE$method\n"
"    }\n"
"    else if(selectedTask == 'Optimization' ){\n"
"      methodSetting= inputFile$settingsOpt$method\n"
"    }\n"
"    else{\n"
"      return()\n"
"    }\n"
"  \n"
"    strOut= ''\n"
"    namesMethod= paste0(toupper(substring(names(methodSetting),1,1)),substring(names(methodSetting),2))\n"
"    strOut= paste('<pre><b>',namesMethod[[1]],'</b>:',methodSetting[[1]],'<br><pre>')\n"
"    for (i in 2:length(namesMethod)){\n"
"      strOut= paste(strOut, '<b>',namesMethod[[i]],'</b>:&nbsp ', methodSetting[[i]], '<br>')\n"
"    }\n"
"    return(paste(strOut,'</pre></pre>'))\n"
"  })\n"
"    \n"
"  paramList <- function () {\n"
"    if (is.null(inputFile$rootnode))\n"
"      return()\n"
"    \n"
"    selectedTask = selection()\n"
"    if (selectedTask == 'Parameter Estimation' ){\n"
"      xmlList= inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[6]][[2]][[4]]\n"
"    }\n"
"    else if(selectedTask == 'Optimization' ){\n"
"      xmlList= inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[5]][[2]][[6]]\n"
"    }\n"
"    else{\n"
"      return()\n"
"    }\n"
"    \n"
"    numParameters= xmlSize(xmlChildren(xmlList))\n"
"    if (numParameters < 1)\n"
"      return()\n"
"    resTable <- setNames(data.frame(matrix(ncol = 4, nrow = numParameters)), c('LowerBound', 'Parameter', 'UpperBound','StartValue'))\n"
"    for (i in 1:numParameters){\n"
"      xmlListIN <- xmlChildren(xmlList[[i]])\n"
"      for (j in 1:xmlSize(xmlListIN)){\n"
"        checkParam = names(xmlListIN) == 'Parameter'\n"
"        if (checkParam[j]){\n"
"          paramValue= xmlToList(xmlListIN[[j]])\n"
"          if (paramValue[[1]] == 'LowerBound'){\n"
"            resTable$LowerBound[i] = paramValue[[3]]\n"
"          }\n"
"          else if (paramValue[[1]]== 'ObjectCN'){\n"
"            resTable$Parameter[i] = gsub(',Reference=','.',gsub('.*Vector=','',paramValue[[3]]))\n"
"          }\n"
"          else if (paramValue[[1]]== 'UpperBound'){\n"
"            resTable$UpperBound[i] = paramValue[[3]]\n"
"          }\n"
"          else if (paramValue[[1]]== 'StartValue'){\n"
"            resTable$StartValue[i] = paramValue[[3]]\n"
"          }}}}\n"
"    return(resTable)\n"
"  }\n"
"  \n"
"  constrList <- function () {\n"
"    if (is.null(inputFile$rootnode))\n"
"      return()\n"
"    \n"
"    selectedTask = selection()\n"
"    if (selectedTask == 'Parameter Estimation' ){\n"
"      xmlList= inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[6]][[2]][[5]]\n"
"    }\n"
"    else if(selectedTask == 'Optimization' ){\n"
"      xmlList= inputFile$rootnode$doc$children$COPASI[names(inputFile$rootnode$doc$children$COPASI)=='ListOfTasks']$ListOfTasks[[5]][[2]][[7]]\n"
"    }\n"
"    else{\n"
"      return()\n"
"    }\n"
"\n"
"    numParameters= xmlSize(xmlChildren(xmlList))\n"
"    if (numParameters < 1)\n"
"      return()\n"
"    resTable <- setNames(data.frame(matrix(ncol = 3, nrow = numParameters)), c('LowerBound', 'Parameter', 'UpperBound'))\n"
"    \n"
"    for (i in 1:numParameters){\n"
"      xmlListIN <- xmlChildren(xmlList[[i]])\n"
"      for (j in 1:xmlSize(xmlListIN)){\n"
"        checkParam = names(xmlListIN) == 'Parameter'\n"
"        if (checkParam[j]){\n"
"          paramValue= xmlToList(xmlListIN[[j]])\n"
"          if (paramValue[[1]] == 'LowerBound'){\n"
"            resTable$LowerBound[i] = paramValue[[3]]\n"
"          }\n"
"          else if (paramValue[[1]]== 'ObjectCN'){\n"
"            resTable$Parameter[i] = gsub(',Reference=','.',gsub('.*Vector=','',paramValue[[3]]))\n"
"          }\n"
"          else if (paramValue[[1]]== 'UpperBound'){\n"
"            resTable$UpperBound[i] = paramValue[[3]]\n"
"            }}}}\n"
"    return(resTable)\n"
"  }\n"
"  \n"
"\n"
"#### To execute different tasks ####\n"
"  resTask <- eventReactive(input$runTask, {\n"
"    modelData <- inputFile$modelData\n"
"    selectedTask <- selection()\n"
"    \n"
"    progress <- shiny::Progress$new() # Create a Progress object\n"
"    on.exit(progress$close()) # To make sure it closes when we exit this reactive, even if there's an error\n"
"    progress$set(message = paste('Running ', selectedTask), value = 0)\n"
"\n"
"    if (selectedTask %in% c('Steady State','Linear Noise Approximation')){\n"
"      if (selectedTask == 'Steady State') settingTask = CoRC::getSS(model=modelData)\n"
"      else settingTask = CoRC::getLNA(model=modelData)\n"
"      settingTask$method$resolution = input$resolution\n"
"      settingTask$method$derivation_factor = input$derivationFac\n"
"      settingTask$method$use_newton = input$useNewton\n"
"      settingTask$method$use_integration = input$useIntegration\n"
"      settingTask$method$use_back_integration = input$useBackIntegration\n"
"      if (selectedTask == 'Steady State') resTask <- tryCatch(CoRC::runSS(calculate_jacobian = input$calculateJacobian,perform_stability_analysis =input$performStabilityAnalysis,method=settingTask$method,model=modelData), warning = function(warning_condition){return(warning_condition) }, error = function(error_condition){return(error_condition) })\n"
"      if (selectedTask == 'Linear Noise Approximation') resTask <- tryCatch(CoRC::runLNA(perform_steady_state_analysis = input$lnaSelection,method=settingTask$method,model=modelData), warning = function(warning_condition){return(warning_condition) }, error = function(error_condition){return(error_condition) })\n"
"    }\n"
"    else if (selectedTask == 'Time Course'){\n"
"      resTask <- tryCatch(CoRC::runTC(duration=input$obsTime,dt=input$obsIntervalSize,start_in_steady_state=input$startSteady,method=input$timeCourseSelection,model=modelData,save_result_in_memory = T), warning = function(warning_condition){return(warning_condition) }, error = function(error_condition){return(error_condition) })\n"
"    }\n"
"    else if(selectedTask == 'Metabolic Control Analysis'){\n"
"      settingTask = CoRC::getMCA(model=modelData)\n"
"      settingTask$method$modulation_factor = input$modulationFactor\n"
"      settingTask$method$use_reder = input$useReder\n"
"      settingTask$method$use_smallbone = input$useSmallbone\n"
"      resTask <- tryCatch(CoRC::runMCA(perform_steady_state_analysis = input$mcaSelection, method= settingTask$method, model=modelData), warning = function(warning_condition){return(warning_condition) }, error = function(error_condition){return(error_condition) })\n"
"    }\n"
"    else if (selectedTask == 'Optimization'){\n"
"      resTask <- tryCatch(CoRC::runOptimization(model=modelData), warning = function(warning_condition){return(warning_condition) }, error = function(error_condition){return(error_condition) })\n"
"    }\n"
"    else if (selectedTask == 'Parameter Estimation'){\n"
"      resTask <- tryCatch(CoRC::runParameterEstimation(model=modelData), warning = function(warning_condition){return(warning_condition) }, error = function(error_condition){return(error_condition) })\n"
"    }\n"
"    else\n"
"      resTask <- 'No Task found'\n"
"\n"
"    return(resTask)\n"
"  })\n"
"  \n"
"#### To download tables for different tasks ####  \n"
"  ## For data download\n"
"  output$downloadData<-downloadHandler(\n"
"    filename = function() { \n"
"      if (is.null(inputFile$dataPaths))\n"
"        return(NULL)\n"
"      paste(sub('\\\\..*$', '',inputFile$modelName) , '.csv', sep='')\n"
"      },\n"
"    content = function(file) {\n"
"      if (is.null(file) || error() != '' || is.null(resTask()))\n"
"        return(NULL)\n"
"      selectedTask <- selection()\n"
"      if (selectedTask == 'Steady State'){\n"
"        writeData <- resTask()$species[,c('name','concentration','rate','transition_time')]\n"
"      }\n"
"      else if (selectedTask == 'Time Course' && 'Time' %in% names(resTask()$result) && !is.null(input$columns)){\n"
"        writeData <- resTask()$result[, c('Time',input$columns), drop = FALSE]\n"
"      }\n"
"      else if(selectedTask == 'Metabolic Control Analysis'){\n"
"        writeData <- resTask()$elasticities_unscaled\n"
"      }\n"
"      else  if(selectedTask == 'Optimization'){\n"
"        writeData <- resTask()$parameters\n"
"      }\n"
"      else if(selectedTask == 'Parameter Estimation'){\n"
"        writeData <- resTask()$parameter\n"
"      }\n"
"      else if (selectedTask == 'Linear Noise Approximation'){\n"
"        writeData <- resTask()$covariance_matrix\n"
"      }\n"
"      else\n"
"        writeData <- 'No Data found'\n"
"      \n"
"      write.csv(writeData,file)\n"
"    }\n"
"  )\n"
"  \n"
"  ## For model download\n"
"  output$downloadModel<-downloadHandler(\n"
"    filename = function() { \n"
"      if (is.null(inputFile$dataPaths))\n"
"        return(NULL)\n"
"      paste(sub('\\\\..*$', '',inputFile$modelName) , '.zip', sep='')\n"
"    },\n"
"    content = function(file) {\n"
"      zipr(file,inputFile$dataPaths)\n"
"    },\n"
"    contentType = 'application/zip'\n"
"  )\n"
"  \n"
"#### To render output tables for different tasks ####\n"
"  \n"
"  ## Output task-specific results\n"
"  output$tableResults1 <- DT::renderDataTable({\n"
"    if (error() != '' || is.null(resTask()))\n"
"      return(NULL)\n"
"    \n"
"    selectedTask <- selection()\n"
"    if (selectedTask == 'Steady State'){\n"
"      return(resTask()$species[,c('name','concentration','rate','transition_time')])\n"
"    }\n"
"    else if (selectedTask == 'Time Course' && 'Time' %in% names(resTask()$result) && !is.null(input$columns)){\n"
"      return(resTask()$result[, c('Time',input$columns), drop = FALSE])\n"
"    }\n"
"    else if(selectedTask == 'Metabolic Control Analysis'){\n"
"      return(resTask()$elasticities_unscaled)\n"
"    }\n"
"    else if(selectedTask %in% c('Optimization','Parameter Estimation') && !is.null(resTask()$main)){\n"
"      data <- t(as.data.frame(resTask()$main))\n"
"      colnames(data) <- c('Value')\n"
"      return(data)\n"
"    }\n"
"    else\n"
"      return(NULL)\n"
"    },options = list(scrollX = TRUE, scrollY = '400px'))\n"
"  \n"
"  \n"
"  output$tableResults2 <- DT::renderDataTable({\n"
"    if (error() != '' || is.null(resTask()))\n"
"      return(NULL)\n"
"    \n"
"    selectedTask <- selection()\n"
"    if (selectedTask == 'Steady State'){\n"
"      colNames <- colnames(resTask()$jacobian_complete)\n"
"      data <- data.frame(resTask()$jacobian_complete)\n"
"      data <- formattable(data, list(area(col = colnames(data)) ~ color_tile('lightpink', 'lightgreen')))\n"
"      colnames(data) <- colNames\n"
"      return(as.datatable(data,options = list(scrollX = TRUE, scrollY = '400px')))\n"
"    }\n"
"    else if(selectedTask == 'Metabolic Control Analysis'){\n"
"      return(resTask()$elasticities_unscaled)\n"
"    }\n"
"    else if(selectedTask == 'Optimization'){\n"
"      return(resTask()$parameters)\n"
"    }\n"
"    else if(selectedTask == 'Parameter Estimation'){\n"
"      return(resTask()$parameter)\n"
"    }\n"
"    else if(selectedTask == 'Linear Noise Approximation'){\n"
"	   colNames <- colnames(resTask()$covariance_matrix)\n"
"      data <- data.frame(resTask()$covariance_matrix)\n"
"      data <- formattable(data, list(area(col = colnames(data)) ~ color_tile('lightpink', 'lightgreen')))\n"
"      colnames(data) <- colNames\n"
"      return(as.datatable(data,options = list(scrollX = TRUE, scrollY = '400px')))\n"
"    }\n"
"    else\n"
"      return(NULL)\n"
"  })\n"
"  \n"
"  output$tablePEexp <- DT::renderDataTable({\n"
"    if (error() != '' || is.null(resTask()))\n"
"      return(NULL)\n"
"    return(resTask()$experiments)\n"
"  },options = list(scrollX = TRUE, scrollY = '400px'))\n"
"  \n"
"  \n"
"  ## Display the selected parameters and constraints \n"
"  output$tableParameterList <- DT::renderDataTable({\n"
"    if(!is.null(paramList())) return(paramList())\n"
"  },options = list(scrollX = TRUE, scrollY = '200px'))\n"
"  \n"
"  output$tableConstraintList <- DT::renderDataTable({\n"
"    if (!is.null(constrList())) return(constrList())\n"
"  },options = list(scrollX = TRUE, scrollY = '200px'))\n"
"  \n"
"  ## Display information of the loaded model\n"
"  output$tableModel <- DT::renderDataTable({\n"
"    if (is.null(inputFile$modelData))\n"
"      return()\n"
"    selectedTask <- selection()\n"
"    tableModel <-  data.frame()\n"
"    if (selectedTask == 'Compartments'){\n"
"      tableModel <- inputFile$compartments\n"
"      if (!is.null(tableModel)){\n"
"        tableModel <- tableModel[,c(-1)]    \n"
"      }}\n"
"    else if (selectedTask == 'Species'){\n"
"      tableModel <- inputFile$species\n"
"      tableModel <- tableModel[,c(-1,-7,-9,-11)]\n"
"    }\n"
"    else if (selectedTask == 'Reactions'){\n"
"      tableModel <- inputFile$reactions\n"
"      if (!is.null(tableModel)){\n"
"        tableModel <- tableModel[,c('name','reaction','rate_law','flux')]\n"
"        tableModel$rate_law <- gsub('.*\\\\[|\\\\]', '', tableModel$rate_law)        \n"
"      }}\n"
"    else if (selectedTask == 'Global Quantities'){\n"
"      tableModel <- inputFile$globalQuantities\n"
"      tableModel <- tableModel[,-1]\n"
"    } \n"
"    else if (selectedTask == 'Events'){\n"
"      tableModel <- data.frame(inputFile$events)\n"
"      if (!is.null(tableModel)){\n"
"        tableModel <- tableModel[,-1]\n"
"        tableModel$assignment_target <- gsub('.*\\\\(|\\\\)', '', tableModel$assignment_target)\n"
"        tableModel$assignment_expression <- gsub('.*\\\\(|\\\\)', '', tableModel$assignment_expression)\n"
"      }} \n"
"    else if (selectedTask == 'Parameters'){\n"
"      tableModel <- inputFile$parameters\n"
"      if (!is.null(tableModel)){\n"
"        tableModel <- tableModel[,-1]\n"
"        tableModel$mapping <- gsub('.*\\\\[|\\\\]', '', tableModel$mapping)  \n"
"      }}\n"
"    return(tableModel)\n"
"  },options = list(scrollX = TRUE, scrollY = '400px'))\n"
"  \n"
"  output$tableLM <- DT::renderDataTable({\n"
"    if (is.null(inputFile$modelData))\n"
"      return()\n"
"    colNames <- colnames(inputFile$linkMatrix)\n"
"    data <- data.frame(inputFile$linkMatrix)\n"
"    data <- formattable(data, list(area(col = colnames(data)) ~ color_tile('lightpink', 'lightgreen')))\n"
"    colnames(data) <- colNames\n"
"    return(as.datatable(data,options = list(scrollX = TRUE, scrollY = '400px')))\n"
"  })\n"
"  output$tableStoich <- DT::renderDataTable({\n"
"    if (is.null(inputFile$modelData))\n"
"      return()\n"
"    colNames <- colnames(inputFile$stoichiometry)\n"
"    data <- data.frame(inputFile$stoichiometry)\n"
"    data <- formattable(data, list(area(col = colnames(data)) ~ color_tile('lightpink', 'lightgreen')))\n"
"    colnames(data) <- colNames\n"
"    return(as.datatable(data,options = list(scrollX = TRUE, scrollY = '400px')))\n"
"  })\n"
"\n"
"#### To render UI and plots for different tasks ####\n"
"  output$plotOverview <- renderPlot({\n"
"    selectedTask <- selection()\n"
"    if (selectedTask == 'Species'){\n"
"      tableSpecies <- inputFile$species\n"
"      if (!is.null(tableSpecies) && nrow(tableSpecies) !=0 ){\n"
"        ylabel <- paste('Concentration (',tableSpecies$unit[1], ')')\n"
"        barplot(tableSpecies$initial_concentration, main='Species overview',  ylab=ylabel, names.arg=tableSpecies$name, cex.names=0.8,las=2)\n"
"      }\n"
"    }\n"
"    else if (selectedTask == 'Global Quantities'){\n"
"      tableGlobalQuantities <- inputFile$globalQuantities\n"
"      if (!is.null(tableGlobalQuantities) && nrow(tableGlobalQuantities) !=0 ){\n"
"        barplot(tableGlobalQuantities$initial_value, main='Global Quantities overview', ylab= 'Initial value', names.arg=tableGlobalQuantities$name, cex.names=0.8,las=2)\n"
"      }\n"
"    }\n"
"    else if (selectedTask == 'Parameters'){\n"
"      tableParameters <- inputFile$parameters\n"
"      if (!is.null(tableParameters) && nrow(tableParameters) !=0 && !all(is.na(tableParameters$value))){\n"
"        barplot(tableParameters$value, main='Parameters overview', ylab='Value', names.arg=tableParameters$name, cex.names=0.8,las=2)\n"
"      }\n"
"    }\n"
"  })\n"
"  \n"
"  output$plotTC <- renderPlot({\n"
"    if (error() != '' || is.null(resTask()) || is.null(input$columns))\n"
"      return(NULL)\n"
"    \n"
"    selectedTask <- selection()\n"
"    data <- resTask()$result\n"
"    if (selectedTask == 'Time Course' && 'Time' %in% names(data)){\n"
"      data <- data[, c('Time',input$columns), drop = FALSE]\n"
"      melted <- melt(data,id.vars='Time')\n"
"      colnames(melted)[2:3] <- c('Species', 'Number')\n"
"      plot <- ggplot(melted, aes(x=Time, y=Number, group=Species, color= Species)) + geom_line(size = 1) + theme_classic(base_size = 18) + ggtitle('Time-course of selected species') + ylab('Concentration') + xlab('Time (s)') + theme_pm()\n"
"      print(plot)\n"
"    }\n"
"    else{\n"
"      textOutput('error')\n"
"    }\n"
"  })\n"
"\n"
"  ## To load the output UI showing table/Plot\n"
"  output$show_output<- renderUI({\n"
"    selectedTask <- selection()\n"
"    if (is.null(inputFile$modelData))\n"
"      return(NULL)\n"
"    if (selectedTask %in% c('Species','Global Quantities','Parameters')){\n"
"      tabsetPanel(id = 'mdl',tabPanel('Table',DT::dataTableOutput('tableModel')),tabPanel('Overview', plotOutput('plotOverview')))\n"
"    }\n"
"    else if (selectedTask %in% c('Reactions','Compartments', 'Events')){\n"
"        tabPanel('mdlTable',DT::dataTableOutput('tableModel'))\n"
"    }\n"
"    else if(selectedTask == 'Stoichiometry'){\n"
"      tabsetPanel(id = 'mdlTable',tabPanel('Stoichiometry Matrix',DT::dataTableOutput('tableStoich')),tabPanel('Link Matrix',DT::dataTableOutput('tableLM')))\n"
"    }\n"
"    else if (selectedTask == 'Time Course'){\n"
"      tabsetPanel(id = 'TC',tabPanel('Time Course',DT::dataTableOutput('tableResults1')),tabPanel('Plot', plotOutput('plotTC')))\n"
"    }\n"
"    else if (selectedTask == 'Steady State'){\n"
"      tabsetPanel(id = 'SS',tabPanel('Steady State', DT::dataTableOutput('tableResults1')),tabPanel('Jacobian', DT::dataTableOutput('tableResults2')))\n"
"    }\n"
"    else if(selectedTask == 'Metabolic Control Analysis'){\n"
"      tabPanel('Table',DT::dataTableOutput('tableResults1'))\n"
"    }\n"
"    else if(selectedTask == 'Optimization'){\n"
"      tabsetPanel(id = 'PE',tabPanel('Main',DT::dataTableOutput('tableResults1')),tabPanel('Optimized Parameters',DT::dataTableOutput('tableResults2')))\n"
"    }\n"
"    else if(selectedTask == 'Parameter Estimation'){\n"
"      tabsetPanel(id = 'PE',tabPanel('Main',DT::dataTableOutput('tableResults1')),tabPanel('Fitted Parameters',DT::dataTableOutput('tableResults2')),tabPanel('Experiments', DT::dataTableOutput('tablePEexp')))\n"
"    }\n"
"    else if(selectedTask == 'Linear Noise Approximation'){\n"
"      tabPanel('Table',DT::dataTableOutput('tableResults2'))\n"
"    }\n"
"    else{\n"
"    }\n"
"  })\n"
"  output$SSmsg <- renderText({\n"
"    selectedTask <- selection()\n"
"    resStr =ifelse(selectedTask == 'Steady State' && !is.null(resTask()$result),resTask()$result,ifelse(!is.null(resTask()$result_ss),resTask()$result_ss,return(NULL)))\n"
"    if(resStr == 'found') return('<pre> <b> Steady state found !!</b></pre>')\n"
"    else if(resStr == 'foundEquilibrium') return('<pre> <b> Equilibrium steady state found!!</b></pre>')\n"
"    else return('<pre> <b> No steady state found !!</b></pre>')\n"
"  })\n"
"  \n"
"#### To choose species for table and plot output ** ONLY FOR TIME_COURSE ** ####\n"
"  output$choose_columns <- renderUI({\n"
"    # If missing input, return to avoid error later in function\n"
"    if(error() != '' || is.null(resTask()))\n"
"      return(NULL)\n"
"    selectedTask <- selection()\n"
"    output = tagList()\n"
"    if (selectedTask %in% c('Steady State','Linear Noise Approximation')){\n"
"      output[[1]] =  htmlOutput('SSmsg')\n"
"    }\n"
"    else if (selectedTask == 'Time Course' && 'Time' %in% names(resTask()$result)){\n"
"      data <- resTask()$result\n"
"      # Get the data set with the appropriate name\n"
"      melted <- melt(data,id.vars='Time')\n"
"      colnames(melted)[2:3] <- c('Species', 'Number')\n"
"      colnames <- unique(melted$Species)\n"
"      output[[1]] = actionButton('showAll', 'Show/Hide All')\n"
"      # Create the checkboxes and select them all by default\n"
"      output[[2]] = checkboxGroupInput('columns', '', choices  = colnames, selected = colnames, inline = T)\n"
"    }\n"
"    return(output)\n"
"  })\n"
"  \n"
"  observeEvent(input$showAll,{\n"
"    if(error() != '' || is.null(resTask()))\n"
"      return(NULL)\n"
"    \n"
"    data <- resTask()$result\n"
"    melted <- melt(data,id.vars='Time')\n"
"    colnames(melted)[2:3] <- c('Species', 'Number')\n"
"    colnames <- unique(melted$Species)\n"
"    if (input$showAll %% 2 == 0){\n"
"      updateCheckboxGroupInput(session=session,'columns', choices= colnames, selected= colnames,inline = T)\n"
"    }\n"
"    else {\n"
"      updateCheckboxGroupInput(session=session,'columns', choices= colnames, selected= NULL,inline = T)\n"
"    }\n"
"  })\n"
"\n"
"#### To generate options interface for tasks ####\n"
"  output$choose_options <- renderUI({\n"
"    # If missing input, return to avoid error later in function\n"
"    if(length(get_selected(input$taskSelection))==0)\n"
"      return(NULL)\n"
"    else{\n"
"      textOutput('selection')\n"
"    }\n"
"    output = tagList()\n"
"    selectedTask <- selection()\n"
"    if (selectedTask %in% c('Reactions','Species','Compartments', 'Global Quantities','Events','Parameters','Stoichiometry')){\n"
"      output[[1]] = ''\n"
"    }\n"
"    else if (selectedTask %in% c('Steady State','Linear Noise Approximation')){\n"
"      if (selectedTask == 'Steady State'){\n"
"        if (!is.null(inputFile$modelData)) settingTask = CoRC::getSS(model=inputFile$modelData)\n"
"        output[[1]] = splitLayout(checkboxInput('calculateJacobian','calculate Jacobian', value= ifelse(is.null(inputFile$modelData), T, settingTask$calculate_jacobian)),checkboxInput('performStabilityAnalysis','perform Stability Analysis', value= ifelse(is.null(inputFile$modelData), T, settingTask$perform_stability_analysis)))\n"
"      }\n"
"      else {\n"
"        if (!is.null(inputFile$modelData))settingTask = CoRC::getLNA(model=inputFile$modelData)\n"
"        output[[1]] = checkboxInput('lnaSelection','perform Steady State Analysis',value = ifelse(is.null(inputFile$modelData), T, settingTask$perform_steady_state_analysis))\n"
"      }\n"
"      output[[2]] = splitLayout(numericInput('resolution', 'Resolution:', ifelse(is.null(inputFile$modelData), 1e-9, settingTask$method$resolution), min = 1e-9, max = 1),numericInput('derivationFac', 'Derivation Factor:', ifelse(is.null(inputFile$modelData), 1e-3, settingTask$method$derivation_factor), min = 1e-3, max = 1))\n"
"      output[[3]] = splitLayout(checkboxInput('useNewton','Use Newton', value= ifelse(is.null(inputFile$modelData), T, settingTask$method$use_newton)),checkboxInput('useIntegration','Use Integration', value= ifelse(is.null(inputFile$modelData), T, settingTask$method$use_integration)),checkboxInput('useBackIntegration','Use Back Integration', value= ifelse(is.null(inputFile$modelData), F, settingTask$method$use_back_integration)))\n"
"      output[[4]] = actionButton('runTask', 'Run Task',icon=icon('angle-double-right'))\n"
"      output[[5]] = downloadButton('downloadData', 'Download Results')\n"
"    }\n"
"    else if (selectedTask == 'Time Course'){\n"
"      output[[1]] = splitLayout(numericInput('obsTime', 'Duration [s]:', ifelse(is.null(inputFile$modelData), 10, inputFile$settingsTC$duration), min = 1, max = 1000),numericInput('obsIntervalSize', 'Interval Size [s]:', ifelse(is.null(inputFile$modelData), 1, inputFile$settingsTC$dt), min = 0.0001, max = 100))\n"
"      output[[2]] = checkboxInput('startSteady','start in Steady State', value= ifelse(is.null(inputFile$modelData), F, inputFile$settingsTC$start_in_steady_state))\n"
"      output[[3]] = selectInput('timeCourseSelection', 'Select a Method:', choices = c('Deterministic (LSODA)'='deterministic'\n"
"                                                                                       ,'Stochastic (Gibson + Bruck) '='stochastic'\n"
"                                                                                       ,'Stochastic (Direct method)'='directMethod'\n"
"                                                                                       ,'Stochastic (Tau leap)'='tauLeap'\n"
"                                                                                       ,'Stochastic (Adaptive SSA)'='adaptiveSA'\n"
"                                                                                       ,'Hybrid (Runge-Kutta)'='hybrid'\n"
"                                                                                       ,'Hybrid (LSODA)'='hybridLSODA'\n"
"                                                                                       #,'Hybrid (RK45)'='hybridODE45'\n"
"                                                                                       ,'SDE solver (RI5)'='stochasticRunkeKuttaRI5')\n"
"                                ,selected = ifelse(is.null(inputFile$modelData), 'deterministic', inputFile$settingsTC$method$method))\n"
"      output[[4]] = actionButton('runTask', 'Run Task',icon=icon('angle-double-right'))\n"
"      output[[5]] = downloadButton('downloadData', 'Download Results')\n"
"    }\n"
"    else if (selectedTask == 'Metabolic Control Analysis'){\n"
"      if (!is.null(inputFile$modelData)) settingTask = CoRC::getMCA(model=inputFile$modelData)\n"
"      output[[1]] = checkboxInput('mcaSelection','perform Steady State Analysis',value = T)\n"
"      output[[2]] = numericInput('modulationFactor', 'Modulation Factor:', ifelse(is.null(inputFile$modelData), 1e-9, settingTask$method$modulation_factor), min = 1e-9, max = 1)\n"
"      output[[3]] = splitLayout(checkboxInput('useReder','Use Reder', value= ifelse(is.null(inputFile$modelData), T, settingTask$method$use_reder)),checkboxInput('useSmallbone','Use Smallbone', value= ifelse(is.null(inputFile$modelData), T, settingTask$method$use_smallbone)))\n"
"      output[[4]] = actionButton('runTask', 'Run Task',icon=icon('angle-double-right'))\n"
"      output[[5]] = downloadButton('downloadData', 'Download Results')\n"
"    }\n"
"    else if (selectedTask == 'Optimization'){\n"
"      output[[1]] = tabsetPanel(id = 'PE',tabPanel('Parameters', DT::dataTableOutput('tableParameterList')),tabPanel('Constraints', DT::dataTableOutput('tableConstraintList')) )\n"
"      output[[2]] = htmlOutput('selectedMethod')\n"
"      output[[3]] = actionButton('runTask', 'Run Task',icon=icon('angle-double-right'))\n"
"      output[[4]] = downloadButton('downloadData', 'Download Results')\n"
"    }\n"
"    else if (selectedTask == 'Parameter Estimation'){\n"
"      output[[1]] = tabsetPanel(id = 'PE',tabPanel('Parameters', DT::dataTableOutput('tableParameterList')),tabPanel('Constraints', DT::dataTableOutput('tableConstraintList')) )\n"
"      output[[2]] = htmlOutput('selectedMethod')\n"
"      output[[3]] = actionButton('runTask', 'Run Task',icon=icon('angle-double-right'))\n"
"      output[[4]] = downloadButton('downloadData', 'Download Results')\n"
"    }\n"
"    return(output)\n"
"  })\n"
"  \n"
"  ### Tree structure for task selection\n"
"  output$taskSelection <- renderTree({ \n"
"    structTree =list('Model'= structure(list('Compartments'= structure('1',sticon=''),'Species'= structure('2',sticon=''),'Reactions'= structure('3',sticon=''),'Global Quantities'= structure('4',sticon=''),'Events'= structure('5',sticon=''),'Parameters'= structure('6',sticon=''),'Stoichiometry'= structure('7',sticon='')),sticon='')\n"
"                     ,'Tasks'= structure(list('Steady State'= structure('1',sticon=''),'Time Course'= structure('2',sticon=''),'Metabolic Control Analysis'= structure('3',sticon=''),'Optimization'= structure('4',sticon=''),'Parameter Estimation'= structure('5',sticon=''),'Linear Noise Approximation'= structure('6',sticon='')), sticon=''))\n"
"    attr(structTree[[1]],'stopened')=TRUE \n"
"    attr(structTree[[2]],'stopened')=TRUE \n"
"    structTree\n"
"  })\n"
"}\n";