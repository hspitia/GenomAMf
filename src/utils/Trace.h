/**
 * @file Trace.h
 * @date 21/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Trace.h
 *   Created on:  21/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */


#ifndef TRACE_H_
#define TRACE_H_

#ifdef DEBUG_MODE
#define TRACE(arg) (std::cout << "\nDEBUG - " << __FILE__ << ", line: " << arg << std::endl)
#define DEBUG(arg) (std::cout << "\t" << arg)
#else
#define TRACE(arg) sizeof(std::cout << arg << std::endl)
#define DEBUG(arg) sizeof(std::cout << arg)
#endif


#endif /* TRACE_H_ */
