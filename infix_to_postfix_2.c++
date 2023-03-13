template <class myType>
void infixToPostfix<myType>::convertToPostfix()
{
    linkedStack<char> newS; //creating a new char stack
    string output; //creating the postfix output string

    for(int i = 0; i < infx.length(); i++) //cycle through the entire string
    {
        if (isgraph(infx[i])) //skip spaces
        {
            if (isalpha(infx[i])) //if the char is a letter (caps or uncaps)
            {
                output += infx[i]; //append it to output
            }
            else
            {
                if (newS.isEmptyStack()) newS.push(infx[i]);
                else if (precedence(infx[i], newS.top()) //check if the current char has higher precedence than the top of the stack, or if the stack is empty
                {
                    newS.push(infx[i]); //push the current char onto the stack
                }
                else if (infx[i] == ')') //check if the current char is a closing paren
                {
                    for(;;)
                    {
                        if (newS.isEmptyStack()) break;
                        if (newS.top() != '(') //check if the top of the stack isn't an open paren
                        {
                            output += newS.top(); //append the top of the stack to the output
                            newS.pop(); //pop the top of the stack off
                        }
                        else //the top of the stack is a (
                        {
                            newS.pop(); //pop the ( off the stack
                            break; //break out of the for loop
                        }
                    }
                }
                else //the current char doesn't have higher precedence than the top of the stack
                {
                    output += newS.top(); //append to the top of the stack to output
                    newS.pop(); //pop off the top of the stack
                    newS.push(infx[i]); //put the current char onto the top of the stack
                }
            }
        }
    }

    while (!newS.isEmptyStack()) //not sure if this works, assuming we're at the end of the line at this point, and if there's anything on the stack we need to append it to the output
    {
        output += newS.top();
        newS.pop();
    }

    pfx = output; //setting pfx to the output (pfx is the class variable for the postfix output)

}