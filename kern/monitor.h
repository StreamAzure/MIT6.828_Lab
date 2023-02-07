#ifndef JOS_KERN_MONITOR_H
#define JOS_KERN_MONITOR_H
#ifndef JOS_KERNEL
# error "This is a JOS kernel header; user programs should not #include it"
#endif

struct Trapframe;

// Activate the kernel monitor,
// optionally providing a trap frame indicating the current state
// (NULL if none).
void monitor(struct Trapframe *tf);

// Functions implementing monitor commands.
int mon_help(int argc, char **argv, struct Trapframe *tf);
int mon_kerninfo(int argc, char **argv, struct Trapframe *tf);
int mon_backtrace(int argc, char **argv, struct Trapframe *tf);
int mon_meow(int argc, char **argv, struct Trapframe *tf);
int mon_showmappings(int argc, char **argv, struct Trapframe *tf);
int mon_change_mappings_permission(int argc, char** argv, struct Trapframe *tf);

static inline uint32_t
xtoi(char* s)
{
    int cnt = 0;
    uint32_t res = 0;
    while(s[cnt]!='\0'){
        res *= 16;
        switch (s[cnt])
        {
        case 'f':
            res += 15;
            break;
        case 'e':
            res += 14;
            break;
        case 'd':
            res += 13;
            break;
        case 'c':
            res += 12;
            break;
        case 'b':
            res += 11;
            break;
        case 'a':
            res += 10;
            break;
        default:
            res += s[cnt]-'0';
            break;
        }
        cnt++;
    }
    return res;
}

#endif	// !JOS_KERN_MONITOR_H
