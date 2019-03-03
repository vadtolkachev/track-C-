#include "VStack.hpp"


#define ASSERT_ERROR()				\
{						\
	int res = checkStack_print(__FILE__, 	\
		__LINE__, __PRETTY_FUNCTION__);	\
	checkStack_dump(__FILE__, 		\
		__LINE__, __PRETTY_FUNCTION__);	\
						\
	if(res)					\
	{					\
		printBadStack();		\
		dumpBadStack();			\
						\
		if(res != NULLPTR_ERR)		\
			fclose(m_dumpFile);	\
		abort();			\
	}					\
}


VStack::VStack() : m_canary1(reinterpret_cast<long unsigned>(&m_canary1)), 
	m_sum1(0), m_sum2(0), m_size(0), 
	m_capacity(0), m_stack(nullptr), 
	m_dumpFile(nullptr),
	m_canary2(reinterpret_cast<long unsigned>(&m_canary2))
{
	char str[45] = "";
	getDumpFileName(str);
	m_dumpFile = fopen(str, "w");
	assert(errno == 0);

	calcSum1();
	calcSum2();

	dumpStack("Stack created");
}


VStack::VStack(const VStack &stack) : 
	m_canary1(reinterpret_cast<long unsigned>(&m_canary1)), 
	m_sum1(0), m_sum2(0), m_size(stack.getSize()),
	m_capacity(stack.getCapacity()), m_stack(nullptr),
	m_dumpFile(nullptr),
	m_canary2(reinterpret_cast<long unsigned>(&m_canary2))
{
	char str[45] = "";
	getDumpFileName(str);
	m_dumpFile = fopen(str, "w");
	assert(errno == 0);

	calcSum1();
	calcSum2();

	dumpStack("Stack created");

	//TODO	
}


VStack::~VStack()
{
	ASSERT_ERROR();
	free(m_stack);
	
	fprintf(m_dumpFile, "Stack destroyed\n[%p]\n\n\n", (void *)this);

	fclose(m_dumpFile);
	assert(errno == 0);
}


void VStack::getDumpFileName(char str[45]) const
{
	char str1[45] = "logs/stackInfo[";
	char str3[6] = "].log";

	char str2[19] = "";
	sprintf(str2, "%p", (void *)this);

	strcat(str1, str2);
	strcat(str1, str3);
	strcpy(str, str1);
}


int VStack::checkFirstCanary() const
{
	if(m_canary1 != reinterpret_cast<long unsigned>(&m_canary1))
		return CANARY1_ERR;

	return STACK_OK;
}


int VStack::checkSecondCanary() const
{
	if(m_canary2 != reinterpret_cast<long unsigned>(&m_canary2))
		return CANARY2_ERR;

	return STACK_OK;
}


int VStack::checkThirdCanary() const
{
	if((m_capacity != 0) && (m_stack[0] != CANARY3))
		return CANARY3_ERR;

	return STACK_OK;
}


int VStack::checkFourthCanary() const
{
	if((m_capacity != 0) && (m_stack[m_capacity+1] != CANARY4))
		return CANARY4_ERR;

	return STACK_OK;
}


int VStack::checkSize() const
{
	if((m_size < 0) || (m_size > m_capacity))
		return SIZE_ERR;

	return STACK_OK;
}


int VStack::checkCapacity() const
{
	if((m_capacity < 0) || (m_capacity % S_BUF != 0))
		return CAPACITY_ERR;

	return STACK_OK;
}


int VStack::checkPoison(data_t *data) const
{
	for(int i = m_size + 1; i < m_capacity + 1; i++)
	{
		if(data)
			*data = m_stack[i];

		if((m_stack[i] != POISON1) && (m_stack[i] != POISON2))
			return POISON_ERR;
	}

	return STACK_OK;
}


int VStack::checkSum1(long *ref) const
{
	char *pByte = (char*) this;
	long sum1 = 0;

	assert(sizeof(*this) == 56);
	for(int i = 0; i < (int)sizeof(*this); i++)
	{
		if((i >= 24) && (i < 48))
			sum1 += pByte[i];
	}

	if(ref)
		*ref = sum1;

	if(m_sum1 != sum1)
		return SUM1_ERR;

	return STACK_OK;
}


int VStack::checkSum2(long *ref) const
{
	char *pByte = (char*) m_stack;
	long sum2 = 0;

	for(int i = 0; i < (int)sizeof(data_t) * (m_capacity + 2); i++)
	{
		if((i >= 4) && (i < 4*(m_size+1)))
			sum2 += pByte[i];
	}

	if(ref)
		*ref = sum2;

	if(m_sum2 != sum2)
		return SUM2_ERR;

	return STACK_OK;
}


int VStack::checkNullptr() const
{
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wnonnull-compare"
	if(!this)
		return  NULLPTR_ERR;
	#pragma GCC diagnostic pop
	

	return STACK_OK;
}


int VStack::checkStack(data_t *data, long *ref) const
{
	int err = checkNullptr();
	if(err)
		return err; 

	err = checkFirstCanary();
	if(err)
		return err; 

	err = checkSecondCanary();
	if(err)
		return err; 

	err = checkSize();
	if(err)
		return err; 

	err = checkCapacity();
	if(err)
		return err; 

	err = checkSum1(ref);
	if(err)
		return err; 

	err = checkThirdCanary();
	if(err)
		return err; 

	err = checkFourthCanary();
	if(err)
		return err; 

	err = checkPoison(data);
	if(err)
		return err; 

	err = checkSum2(ref);
	if(err)
		return err; 

	return err;
}


int VStack::checkStack_print(const char *file, int line, const char *func) const
{
	data_t data;
	long ref;
	int nErr = checkStack(&data, &ref);

	switch(nErr)
	{
		case NULLPTR_ERR : print_err("", file, line, func, (void *)0, NORM_F);
			break;

		case CANARY1_ERR : print_err("canary1", file, line, func, (void *)&m_canary1, HEX_F);
			break;

		case CANARY2_ERR : print_err("canary2", file, line, func, (void *)&m_canary2, HEX_F);
			break;

		case SIZE_ERR : print_err("size", file, line, func, (void *)&m_size, NORM_F);
			break;

		case CAPACITY_ERR : print_err("capacity", file, line, func, (void *)&m_capacity, NORM_F);
			break;

		case CANARY3_ERR : print_err("canary3", file, line, func, (void *)&m_stack[0], HEX_F);
			break;

		case CANARY4_ERR : print_err("canary4", file, line, func, (void *)&m_stack[m_capacity+1], HEX_F);
			break;

		case POISON_ERR : print_err("not a posion", file, line, func, (void *)&data, NORM_F);
			break;

		case SUM1_ERR : print_err("sum1", file, line, func, (void *)&ref, SUM1_F);
			break;

		case SUM2_ERR : print_err("sum2", file, line, func, (void *)&ref, SUM2_F);
			break;

		case STACK_OK : break;
	
		default : print_err("wrong error", file, line, func, (void *)&nErr, NORM_F);
			break;	
	}
	
	return nErr;
}


int VStack::checkStack_dump(const char *file, int line, const char *func) const
{
	data_t data;
	long ref;
	int nErr = checkStack(&data, &ref);

	switch(nErr)
	{
		case NULLPTR_ERR : dump_err("", file, line, func, (void *)0, HEX_F);
			break;
		
		case CANARY1_ERR : dump_err("canary1", file, line, func, (void *)&m_canary1, HEX_F);
			break;

		case CANARY2_ERR : dump_err("canary2", file, line, func, (void *)&m_canary2, HEX_F);
			break;

		case SIZE_ERR : dump_err("size", file, line, func, (void *)&m_size, NORM_F);
			break;

		case CAPACITY_ERR : dump_err("capacity", file, line, func, (void *)&m_capacity, NORM_F);
			break;

		case CANARY3_ERR : dump_err("canary3", file, line, func, (void *)&m_stack[0], HEX_F);
			break;

		case CANARY4_ERR : dump_err("canary4", file, line, func, (void *)&m_stack[m_capacity+1], HEX_F);
			break;

		case POISON_ERR : dump_err("not a posion", file, line, func, (void *)&data, NORM_F);
			break;

		case SUM1_ERR : dump_err("sum1", file, line, func, (void *)&ref, SUM1_F);
			break;

		case SUM2_ERR : dump_err("sum2", file, line, func, (void *)&ref, SUM2_F);
			break;

		case STACK_OK : break;
	
		default : dump_err("wrong error", file, line, func, (void *)&nErr, NORM_F);
			break;	
	}
	
	return nErr;
}


int VStack::getTop(data_t *res) const
{
	ASSERT_ERROR();
	if(res == nullptr)
		return NULLPTR_ERR;
	
	if(!m_size)
		return EMPTY_ERR;

	*res = m_stack[m_size];
	return SUCCESS;
}


int VStack::getSize() const
{
	ASSERT_ERROR();
	return m_size;
}


int VStack::getCapacity() const
{
	ASSERT_ERROR();
	return m_capacity;
}


int VStack::push(data_t data)
{
	ASSERT_ERROR();

	#ifdef S_DOUBLE
	if(std::isfinite(data) == 0)
		return INF_ERR;
	#endif

	if(m_capacity == m_size)
	{
		data_t *tmp;
		int tmp_size = S_BUF + 2;
		if(m_capacity)
			tmp_size = m_capacity*2 + 2;

		tmp = (data_t *) reallocarray(m_stack, tmp_size, sizeof(data_t));
		if(!tmp)
		{
			ASSERT_ERROR();
			return ALLOC_ERR;
		}

		m_stack = tmp;
		m_capacity = tmp_size - 2;

		if(m_size == 0)
			m_stack[0] = CANARY3;
		
		for(int i = m_size + 1; i < m_capacity + 1; i++)
			m_stack[i] = (data_t)POISON1;
		m_stack[m_capacity + 1] = CANARY4;
	}
	
	m_stack[++m_size] = data;
	
	calcSum1();
	calcSum2();

	dumpStack("Stack push");

	ASSERT_ERROR();
	return SUCCESS;
}


int VStack::pop()
{
	ASSERT_ERROR();

	if(m_size == 0)
		return EMPTY_ERR;

	m_stack[m_size--] = POISON2;
	

	calcSum1();
	calcSum2();

	dumpStack("Stack pop");

	ASSERT_ERROR();
	return SUCCESS;
}


bool VStack::isEmpty() const
{
	ASSERT_ERROR();

	if(m_size)
		return true;

	return false;
}


void VStack::printStack() const
{
	ASSERT_ERROR();
	
	std::cout << "Stack [" << this << "]\n{"
		<< "\n\tcanary1 = 0x" << std::hex << m_canary1 << std::dec
		<< "\n\tsum1 = " << m_sum1 
		<< "\n\tsum2 = " << m_sum2
		<< "\n\tsize = " << m_size 
		<< "\n\tcapacity = " << m_capacity
		<< "\n\tdata[" << m_capacity + 2 << "] [";

	if(m_stack) 
		 std::cout << m_stack;
	else 
		std::cout << "nullptr";
	std::cout << "]\n\t{";
	
	int count = 0;
	if(m_capacity != 0)
		count = m_capacity + 2;
	
	for(int i = 0; i < count; i++)
	{
		std::cout << "\n\t\t";
		if((i > 0) && (i <= m_size))
			std::cout << "*";
		else
		{
			if((i == 0) || (i == m_capacity + 1))
				std::cout << ">";
			else
				std::cout << " ";
		}

		std::cout << "[" << i << "] : ";

		if((i == 0) || (i == m_capacity + 1))
			std::cout << std::hex << "0x" << m_stack[i] << std::dec;
		else
			std::cout << m_stack[i];

		if(i == 0)
			std::cout << " (canary3)";

		if(i == m_capacity + 1)
			std::cout << " (canary4)";

		if((i > m_size) && (i != m_capacity + 1))
			std::cout << " (poison)";
	}
		
	std::cout << "\n\t}\n\tcanary2 = 0x" << std::hex << m_canary2 << std::dec
		<< "\n}\n";
}


void VStack::printBadStack() const
{
	data_t data;
	int nErr = checkStack(&data, nullptr);

	std::cout << "Stack [" << this << "]";
	if(nErr)
		std::cout << " (ERROR!!!)\n";

	if(nErr == NULLPTR_ERR)
	{
		std::cout << "{nullptr!!!}\n";
		return;
	}
	
	std::cout << "{\n\tcanary1 = 0x" << std::hex << m_canary1 << std::dec;

	if(nErr == CANARY1_ERR)
	{
		std::cout << "\n}\n";
		return;
	}

	std::cout << "\n\tcanary2 = 0x" << std::hex << m_canary2 << std::dec;

	if(nErr == CANARY2_ERR)
	{
		std::cout << "\n}\n";
		return;
	}
	
	std::cout << "\n\tsize = " << m_size;	
	std::cout << "\n\tcapacity = " << m_capacity;

	if((nErr == CAPACITY_ERR) || (nErr == SIZE_ERR))
	{
		std::cout << "\n}\n";
		return;
	}
	
	if(nErr == CANARY3_ERR)
	{
		std::cout << "\n\tcanary3 = 0x" << std::hex << m_stack[0] << std::dec << "\n}\n";
		return;
	}

	if(nErr == CANARY4_ERR)
	{
		std::cout << "\n\tcanary4 = 0x" << std::hex << m_stack[m_capacity + 1]<< std::dec << "\n}\n";
		return;
	}
	
	std::cout << "\n\tsum1 = " << m_sum1;

	if(nErr == SUM1_ERR)
	{
		std::cout << "\n}\n";
		return;
	}

	std::cout << "\n\tsum2 = " << m_sum2;

	std::cout << "\n\tdata[" << m_capacity + 2 << "] [";
	if(m_stack) 
		 std::cout << m_stack;
	else 
		std::cout << "nullptr";	
	std::cout << "]\n\t{";

	for(int i = 0; i < m_capacity + 2; i++)
	{
		std::cout << "\n\t\t";
		if((i > 0) && (i <= m_size))
			std::cout << "*";
		else
		{
			if((i == 0) || (i == m_capacity + 1))
				std::cout << ">";
			else
				std::cout << " ";
		}
	
		std::cout << "[" << i << "] : ";

		if((i == 0) || (i == m_capacity + 1))
			std::cout << std::hex << "0x" << m_stack[i] << std::dec;
		else
			std::cout << m_stack[i];

		if(i == 0)
			std::cout << " (canary3)";

		if(i == m_capacity + 1)
			std::cout << " (canary4)";

		if((i > m_size) && (i != m_capacity + 1))
			std::cout << " (poison)";
	}

	std::cout << "\n\t}\n}\n";
}


void VStack::print_err(const char *err, const char *file, int line, const char *func, void *what, int format) const
{
	if(!what)
	{
		printf("%s%s:%d: %s: %sthis = nullptr%s\n", WHITE ,file, line, func, RED, NORM);
		return;
	}
	
	printf("%s%s:%d: %s: %s%s = ", WHITE, file, line, func, RED,err);

	if(format == HEX_F)
		printf("0x%lx%s\n", *(long *)what, NORM);				
			
	if(format == SUM1_F)	 					
		printf("%ld but should be %ld%s\n", m_sum1, *(long *)what, NORM);
									
	if(format == SUM2_F)	 					
		printf("%ld but should be %ld%s\n", m_sum2, *(long *)what, NORM);		
									
	if(format == NORM_F)	 				
		printf("%d%s\n", *(int *)what, NORM);
}


void VStack::dumpStack(const char *str) const
{
	assert(m_dumpFile);

	ASSERT_ERROR();

	fprintf(m_dumpFile, "%s\n", str);

	fprintf(m_dumpFile, "Stack [%p]\n{\n\tcanary1 = 0x%lx\n\tsum1 = %ld\n\tsum2 = %ld", (void *)this, m_canary1, m_sum1, m_sum2);
	fprintf(m_dumpFile, "\n\tsize = %d\n\tcapacity = %d\n\tdata[%d] [", m_size, m_capacity, m_capacity + 2);

	if(m_stack) 
		fprintf(m_dumpFile, "%p", (void *)m_stack);
	else 
		fprintf(m_dumpFile, "nullptr");
	fprintf(m_dumpFile, "]\n\t{");
	
	int count = 0;
	if(m_capacity != 0)
		count = m_capacity + 2;
	
	for(int i = 0; i < count; i++)
	{
		fprintf(m_dumpFile, "\n\t\t");
		if((i > 0) && (i <= m_size))
			fprintf(m_dumpFile, "*");
		else
		{
			if((i == 0) || (i == m_capacity + 1))
				fprintf(m_dumpFile, ">");
			else
				fprintf(m_dumpFile, " ");
		}

		fprintf(m_dumpFile, "[%d] : ", i);

		#ifdef S_INT
		if((i == 0) || (i == m_capacity + 1))
			fprintf(m_dumpFile, "0x%X", m_stack[i]);
		else
			fprintf(m_dumpFile, "%d", m_stack[i]);
		#endif

		#ifdef S_DOUBLE
		if((i == 0) || (i == m_capacity + 1))
			fprintf(m_dumpFile, "0x%A", m_stack[i]);
		else
			fprintf(m_dumpFile, "%lg", m_stack[i]);
		#endif

		if(i == 0)
			fprintf(m_dumpFile, " (canary3)");

		if(i == m_capacity + 1)
			fprintf(m_dumpFile, " (canary4)");

		if((i > m_size) && (i != m_capacity + 1))
			fprintf(m_dumpFile, " (poison)");
	}
		
	fprintf(m_dumpFile, "\n\t}\n\tcanary2 = 0x%lx\n}\n\n\n", m_canary2);
}


void VStack::dumpBadStack() const
{
	if(checkNullptr() == NULLPTR_ERR)
	{
		char str1[45] = "logs/stackInfo[";
		char str3[6] = "].log";

		char str2[8] = "nullptr";
		strcat(str1, str2);
		strcat(str1, str3);
	
		FILE *dumpFile = fopen(str1, "a");
	
		fprintf(dumpFile, "Stack [%p] (ERROR!!!)\n{nullptr}", (void *)this);

		fclose(dumpFile);
		return;
	}

	assert(m_dumpFile);

	data_t data;
	int nErr = checkStack(&data, nullptr);

	fprintf(m_dumpFile, "Stack [%p]", (void *)this);
	if(nErr)
		fprintf(m_dumpFile, " (ERROR!!!)\n");
	
	fprintf(m_dumpFile, "{\n\tcanary1 = 0x%lx", m_canary1);

	if(nErr == CANARY1_ERR)
	{
		fprintf(m_dumpFile, "\n}\n");
		return;
	}

	fprintf(m_dumpFile, "\n\tcanary2 = 0x%lx", m_canary2);

	if(nErr == CANARY2_ERR)
	{
		fprintf(m_dumpFile, "\n}\n");
		return;
	}
	
	fprintf(m_dumpFile, "\n\tsize = %d", m_size);
	fprintf(m_dumpFile, "\n\tcapacity = %d", m_capacity);

	if((nErr == CAPACITY_ERR) || (nErr == SIZE_ERR))
	{
		fprintf(m_dumpFile, "\n}\n");
		return;
	}

	fprintf(m_dumpFile, "\n\tsum1 = %ld", m_sum1);
	
	if(nErr == SUM1_ERR)
	{
		fprintf(m_dumpFile, "\n}\n");
		return;
	}

	fprintf(m_dumpFile, "\n\tsum2 = %ld", m_sum2);

	if(nErr == CANARY3_ERR)
	{
		#ifdef S_INT
		fprintf(m_dumpFile, "\n\tcanary3 = 0x%X\n}\n", m_stack[0]);
		#endif

		#ifdef S_DOUBLE
		fprintf(m_dumpFile, "\n\tcanary3 = 0x%A\n}\n", m_stack[0]);
		#endif
		return;
	}

	if(nErr == CANARY4_ERR)
	{
		#ifdef S_INT
		fprintf(m_dumpFile, "\n\tcanary4 = 0x%X\n}\n", m_stack[m_capacity + 1]);
		#endif

		#ifdef S_DOUBLE
		fprintf(m_dumpFile, "\n\tcanary4 = 0x%A\n}\n", m_stack[m_capacity + 1]);
		#endif
		return;
	}
	
	fprintf(m_dumpFile, "\n\tdata[%d] [", m_capacity + 2);

	if(m_stack) 
		 fprintf(m_dumpFile, "%p", (void *)m_stack);
	else 
		fprintf(m_dumpFile, "nullptr");	
	fprintf(m_dumpFile, "]\n\t{");

	for(int i = 0; i < m_capacity + 2; i++)
	{
		fprintf(m_dumpFile, "\n\t\t");
		if((i > 0) && (i <= m_size))
			fprintf(m_dumpFile, "*");
		else
		{
			if((i == 0) || (i == m_capacity + 1))
				fprintf(m_dumpFile, ">");
			else
				fprintf(m_dumpFile, " ");
		}
	
		fprintf(m_dumpFile, "[%d] : ", i);

		#ifdef S_INT
		if((i == 0) || (i == m_capacity + 1))
			fprintf(m_dumpFile, "0x%X", m_stack[i]);
		else
			fprintf(m_dumpFile, "%d", m_stack[i]);
		#endif

		#ifdef S_DOUBLE
		if((i == 0) || (i == m_capacity + 1))
			fprintf(m_dumpFile, "0x%A", m_stack[i]);
		else
			fprintf(m_dumpFile, "%lg", m_stack[i]);
		#endif

		if(i == 0)
			fprintf(m_dumpFile, " (canary3)");

		if(i == m_capacity + 1)
			fprintf(m_dumpFile, " (canary4)");

		if((i > m_size) && (i != m_capacity + 1))
			fprintf(m_dumpFile, " (poison)");
	}

	fprintf(m_dumpFile, "\n\t}\n}\n\n\n");
}


void VStack::dump_err(const char *err, const char *file, int line, const char *func, void *what, int format) const
{
	
	if(!what)
	{
		char str1[45] = "logs/stackInfo[";
		char str3[6] = "].log";

		char str2[8] = "nullptr";
		strcat(str1, str2);
		strcat(str1, str3);

		FILE *dumpFile = fopen(str1, "w");
	
		fprintf(dumpFile, "%s:%d: %s: this = nullptr\n",file, line, func);

		fclose(dumpFile);
		return;
	}	
	
	fprintf(m_dumpFile, "%s:%d: %s: %s = ",file, line, func, err);

	if(format == HEX_F)
		fprintf(m_dumpFile, "0x%lx\n", *(long *)what);				
			
	if(format == SUM1_F)	 					
		fprintf(m_dumpFile, "%ld but should be %ld\n", m_sum1, *(long *)what);
									
	if(format == SUM2_F)	 					
		fprintf(m_dumpFile, "%ld but should be %ld\n", m_sum2, *(long *)what);		
									
	if(format == NORM_F)	 				
		fprintf(m_dumpFile, "%d\n", *(int *)what);		
}


void VStack::calcSum1()
{
	char *pByte = (char*) this;
	assert(sizeof(*this) == 56);

	m_sum1 = 0;
	for(int i = 0; i < (int)sizeof(*this); i++)
	{
		if((i >= 24) && (i < 48))
			m_sum1 += pByte[i];
	}
}


void VStack::calcSum2()
{
	char *pByte = (char*) m_stack;
	m_sum2 = 0;
	for(int i = 0; i < (int)sizeof(data_t) * (m_capacity + 2); i++)
	{
		if((i >= 4) && (i < 4*(m_size+1)))
			m_sum2 += pByte[i];
	}
}


VStack &VStack::operator=(const VStack &stack)
{
	this->m_size = stack.getSize();
	this->m_capacity = stack.getCapacity();	
	
	//TODO
	return *this;
}

